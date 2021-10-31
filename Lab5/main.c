#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union RGBclr {
    char buffer[3];

    struct {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
    } data;
} RGB;

typedef union Header_of_the_file {
    char buffer[14];

    struct {
        unsigned char Type[2];
        unsigned int Size;
        unsigned short Reserved1;
        unsigned short Reserved2;
        unsigned int OffBits;
    } data;
} FILEHEADER;

typedef union Info_header_of_the_file {
    char buffer[40];
    struct {
        unsigned int Size;
        unsigned int Width;
        unsigned int Height;
        unsigned short Planes;
        unsigned short BitCount;
        unsigned int XPelsPerMeter;
        unsigned int YPelsPerMeter;
        unsigned int ClrUsed;
        unsigned int ClrImportant;
        unsigned int Compression;
        unsigned int SizeImage;
    } data;
} Main_header;


//Считывание пикселов из файла
RGB** Load_RGB_of_file(FILE* F, Main_header Info_header) {
    RGB **Pixel_array = (RGB **) malloc(Info_header.data.Height * sizeof(RGB *));
    for (int i = 0; i < Info_header.data.Height; i++) {
        Pixel_array[i] = (RGB *) malloc(Info_header.data.Width * sizeof(RGB));
    }
    for (int i = Info_header.data.Height - 1; i >= 0; i--) {
        for (int j = 0; j < Info_header.data.Width; j++) {
            fread(Pixel_array[i][j].buffer, sizeof(char), 3, F);
        }
    }
    return Pixel_array;
}


//Генерация бмп
void Create_new_BMP_file(FILE* F, FILEHEADER Header_of_the_file, Main_header Info_header, RGB **Pixel_array) {
    fwrite(&Header_of_the_file.buffer, sizeof(char), 14, F);
    fwrite(&Info_header.buffer, sizeof(char), 40, F);
    for (int i = Info_header.data.Height - 1; i >= 0; i--) {
        for (int j = 0; j < Info_header.data.Width; j++) {
            if (i == 0 || i == Info_header.data.Height - 1) {
                Pixel_array[i][i].data.blue = 255;
                Pixel_array[i][i].data.green = 255;
                Pixel_array[i][i].data.red = 255;
            }
            if (j == 0 || j == Info_header.data.Width - 1) {
                Pixel_array[i][j].data.blue = 255;
                Pixel_array[i][j].data.green = 255;
                Pixel_array[i][j].data.red = 255;
            }
            fwrite(&Pixel_array[i][j].buffer, sizeof(char), 3, F);
        }
    }
}


//Проверка - черный ли пиксель
unsigned int Check_black_color(RGB pixel) {
    return (pixel.data.red == 0 && pixel.data.green == 0 && pixel.data.blue == 0) ? 1 : 0;
}


//Сравнение бмпшников
unsigned int Comparison_of_BMP (Main_header Info_header, RGB** world1, RGB** world2) {
    for (int i = Info_header.data.Height - 1; i >= 0; i--) {
        for (int j = 0; j < Info_header.data.Width; j++) {
            if (Check_black_color(world1[i][j]) != Check_black_color(world2[i][j]))
                return 0;
        }
    }
    return 1;
}


//Копирование бмпшника
RGB** Copy_BMP (Main_header Info_header, RGB** in, RGB** out) {
    for (int i = Info_header.data.Height - 1; i >= 0; i--) {
        for (int j = 0; j < Info_header.data.Width; j++) {
            out[i][j].data = in[i][j].data;
        }
    }
    return out;
}


//Подсчет числа живых пикселов
unsigned int Check_number_of_alive_pixels (Main_header Info_header, RGB** world) {
    unsigned int count = 0;
    for (int i = Info_header.data.Height - 1; i >= 0; i--) {
        for (int j = 0; j < Info_header.data.Width; j++) {
            if (Check_black_color(world[i][j]))
                count++;
        }
    }
    return count;
}


unsigned int Check_size (int x) {
    int i;
    for (i = 0; x != 0; i++, x = x/10) {;}
    return i;
}

int main(int argc, char* argv[]) {
    //Task 14
    char* Name_of_the_file, *New_directory;
    int max_iter = -1, dump_freq = 1;
    //Считывание аргументов командной строки
    if (argc % 2 == 0 || argc == 1) {
        printf("%s", "Error: incorrect data entry\n");
        return 0;
    }
    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--input") == 0) {
            if (i + 1 == argc) {
                printf("%s", "Error: incorrect data entry\n");
                return 0;
            }
            Name_of_the_file = argv[i + 1];
        }
        if (strcmp(argv[i], "--output") == 0) {
            if (i + 1 == argc) {
                printf("%s", "Error: incorrect data entry\n");
                return 0;
            }
            New_directory = argv[i + 1];
        }
        if (strcmp(argv[i], "--max_iter") == 0) {
            if (i + 1 == argc) {
                printf("%s", "Error: incorrect data entry\n");
                return 0;
            }
            sscanf(argv[i + 1], "%d", &max_iter);
        }
        if (strcmp(argv[i], "--dump_freq") == 0) {
            if (i + 1 == argc) {
                printf("%s", "Error: incorrect data entry\n");
                return 0;
            }
            sscanf(argv[i + 1], "%d", &dump_freq);
        }
    }
    FILE* fin = fopen(Name_of_the_file, "r");

    if (fin == NULL) {
        printf("Error: file not found\n");
        return 0;
    }
    fseek(fin, 0, SEEK_SET);
    FILEHEADER header;
    fread(header.buffer, sizeof(char), 14, fin);
    Main_header Info_header;
    fread(Info_header.buffer, sizeof(char), 40, fin);
    RGB** prev_world = Load_RGB_of_file(fin, Info_header);
    fclose(fin);
    RGB **new_world = (RGB**) malloc(Info_header.data.Height * sizeof(RGB*));
    for (int i = 0; i < Info_header.data.Height; i++) {
        new_world[i] = (RGB*) malloc(Info_header.data.Width * sizeof(RGB));
    }
    new_world = Copy_BMP(Info_header, prev_world, new_world);
    unsigned int alive_pixels;
    int k;
    for (k = 0; k != max_iter; k++) {
        for (int i = Info_header.data.Height - 1; i >= 0; i--) {
            for (int j = 0; j < Info_header.data.Width; j++) {
                //Определение числа соседей, чтобы понять закрашивать пиксел в определенный цвет или нет
                unsigned int alive_neighbours = 0;
                int up = i - 1, down = i + 1, right = j + 1, left = j - 1;
                if (i == 0)
                    up = Info_header.data.Height - 1;
                if (i == Info_header.data.Height - 1)
                    down = 0;
                if (j == 0)
                    left = Info_header.data.Width - 1;
                if (j == Info_header.data.Width - 1)
                    right = 0;
                if (Check_black_color(prev_world[down][j])) alive_neighbours++;
                if (Check_black_color(prev_world[up][j])) alive_neighbours++;
                if (Check_black_color(prev_world[i][left])) alive_neighbours++;
                if (Check_black_color(prev_world[i][right])) alive_neighbours++;
                if (Check_black_color(prev_world[up][right])) alive_neighbours++;
                if (Check_black_color(prev_world[down][right])) alive_neighbours++;
                if (Check_black_color(prev_world[up][left])) alive_neighbours++;
                if (Check_black_color(prev_world[down][left])) alive_neighbours++;
                if (Check_black_color(prev_world[i][j])) {
                    if (alive_neighbours < 2 || alive_neighbours > 3){
                        new_world[i][j].data.red = 255;
                        new_world[i][j].data.green = 255;
                        new_world[i][j].data.blue = 255;
                    }

                }
                else {
                    if (alive_neighbours == 3){
                        new_world[i][j].data.red = 0;
                        new_world[i][j].data.green = 0;
                        new_world[i][j].data.blue = 0;
                    }

                }
            }
        }
        alive_pixels = Check_number_of_alive_pixels(Info_header, new_world);
        if (k % dump_freq == 0) {
            char* directoryFileName = calloc(strlen(New_directory) + Check_size(k) + 10, sizeof(char));
            sprintf(directoryFileName, "%s/World%d.bmp", New_directory, k);
            FILE* fout = fopen(directoryFileName, "w");
            Create_new_BMP_file(fout, header, Info_header, new_world);
            fclose(fout);
        }
        if(alive_pixels == 0 || Comparison_of_BMP(Info_header, prev_world, new_world)) {
            break;
        }
        prev_world = Copy_BMP(Info_header, new_world, prev_world);
    }
    char* Name_of_directory = calloc(strlen(New_directory) + Check_size(k) + 10, sizeof(char));
    sprintf(Name_of_directory, "%s/World%d.bmp", New_directory, k);
    FILE* fout = fopen(Name_of_directory, "w");
    Create_new_BMP_file(fout, header, Info_header, new_world);
    fclose(fout);
    return 0;
}