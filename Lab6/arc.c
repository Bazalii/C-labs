#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "qsort_for_value_node.h"

static struct {
    unsigned create_mode:1;
    unsigned extract_mode:1;
    unsigned list_mode:1;
    char* archive_name;
} program_configuration;

static struct{
    char** file_names;
    unsigned amount_of_files;
} input_files;

int main(int argc, char**argv){
    ValueNode* value_count_statistic[256];
    
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
        unsigned char buffer[1];
        FILE* file;
        
        for (int i = 0; i < 256; i++){
            value_count_statistic[i] = (ValueNode*)malloc(sizeof(ValueNode));
            value_count_statistic[i]->value = i;
            value_count_statistic[i]->amout = 0;
        }
        
        for (int i = 0; i < input_files.amount_of_files; i++){
            
            file = fopen(input_files.file_names[i], "rb");

            if (file == NULL){
                printf("File \"%s\" can't be open.", input_files.file_names[i]);
                return 0;
            }
            
            while(fread(buffer, 1, 1, file) != 0){
                value_count_statistic[(int)(buffer[0])]->amout += 1;
            }
            
            value_count_statistic[(int)buffer[0]]->amout += 1;
            fclose(file);
        }
        
        value_node_qsort(value_count_statistic, 0, 255);
    }
    
    return 0;
}
