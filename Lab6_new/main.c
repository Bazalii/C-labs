#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static struct {
    unsigned create_mode:1;
    unsigned extract_mode:1;
    unsigned list_mode:1;
    char* archive_name;
} program_configuration;

static struct{
    char** file_names;
    unsigned amount_of_files;
    int* array;
} input_files;

int main(int argc, char**argv){
    char buf[100];
    int counter = 0;
    int amount;
    char ** filenames, char_buf;
    int * file_size;
    FILE * buffer_file, *archive_file;

    if (argc == 1){
        puts("Options aren't detecting.");
        return 0;
    }
    while (--argc > 0){
        argv++;
        if (strcmp(*argv, "--file") == 0){
            if (argc != 1)
                program_configuration.archive_name = *++argv;
            else{
                puts("Can't find output file name for --file option");
                return 0;
            }
            argc--;
        }

        else if (strcmp(*argv, "--create") == 0)
            program_configuration.create_mode = 1;
        else if (strcmp(*argv, "--extract") == 0)
            program_configuration.extract_mode = 1;
        else if (strcmp(*argv, "--list") == 0)
            program_configuration.list_mode = 1;
        else{
            input_files.amount_of_files = argc;
            input_files.file_names = argv;
            argc = 0;
        }
    }

    if (program_configuration.list_mode + program_configuration.create_mode + program_configuration.extract_mode != 1){
        puts("Something was wrong. No such options or too more options were set.");
        return 0;
    }

    if (program_configuration.create_mode && input_files.amount_of_files == 0){
        puts("No such files for archivete.");
        return 0;
    }


    if (program_configuration.create_mode){
        FILE* file;


        input_files.array = malloc(input_files.amount_of_files * sizeof(int));
        for (int i = 0; i < input_files.amount_of_files; ++i) {
            input_files.array[i] = 0;
        }
        for (int i = 0; i < input_files.amount_of_files; i++){

            file = fopen(input_files.file_names[i], "rb");

            if (file == NULL){
                printf("File \"%s\" can't be open.", input_files.file_names[i]);
                return 0;
            }

            while(fread(buf, 1, 1, file) != 0){
                input_files.array[i] += 1;
            }
            fclose(file);
        }

        FILE *fout;
        strcpy(buf, program_configuration.archive_name);
        strcat(buf, ".arc");
        fout = fopen(buf, "wb");
        sprintf(buf, "%i:", input_files.amount_of_files);
        fwrite(buf, sizeof(char ), strlen(buf), fout);
        for (int i = 0; i < input_files.amount_of_files; ++i) {
            fwrite(input_files.file_names[i], sizeof(char), strlen(input_files.file_names[i]), fout);
            fprintf(fout, ":%i:", input_files.array[i]);
        }

        for (int i = 0; i < input_files.amount_of_files; i++){

            file = fopen(input_files.file_names[i], "rb");

            if (file == NULL){
                printf("File \"%s\" can't be open.", input_files.file_names[i]);
                return 0;
            }

            while(fread(buf, 1, 1, file) != 0){
                fwrite(buf, sizeof(char), 1, fout);
            }
            fclose(file);
        }
    }

    if (program_configuration.extract_mode){
        archive_file = fopen(program_configuration.archive_name, "rb");
        fscanf(archive_file, "%i:", &amount);
        filenames = malloc(sizeof(char*) * amount);
        file_size = malloc(sizeof(int) * amount);
        for (int i = 0; i < amount; ++i) {
            filenames[i] = malloc(sizeof(char) * 100);
            while((char_buf = getc(archive_file)) != ':'){
                filenames[i][counter] = char_buf;
                counter++;
            }
            filenames[i][counter] = '\0';
            counter = 0;
            fscanf(archive_file, "%i:", file_size + i);
        }
        for (int i = 0; i < amount; ++i) {
            buffer_file = fopen(filenames[i], "wb");
            for (int j = 0; j < file_size[i]; ++j) {
                fread(&char_buf, 1, 1, archive_file);
                fwrite(&char_buf, 1, 1, buffer_file);
            }
            fclose(buffer_file);
        }
    }

    if (program_configuration.list_mode){
        archive_file = fopen(program_configuration.archive_name, "rb");
        fscanf(archive_file, "%i:", &amount);
        filenames = malloc(sizeof(char*) * amount);
        for (int i = 0; i < amount; ++i) {
            filenames[i] = malloc(sizeof(char) * 100);
            while((char_buf = getc(archive_file)) != ':'){
                filenames[i][counter] = char_buf;
                counter++;
            }
            filenames[i][counter] = '\0';
            counter = 0;
            fscanf(archive_file, "%i:", buf);
        }
        for (int i = 0; i < amount; ++i) {
            printf("%s\n", filenames[i]);

        }
    }
    return 0;
}
