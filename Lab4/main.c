#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef union Main_Frame
{
    char buffer[10];

    struct
    {
        unsigned char frame_ID[4];
        unsigned int size;
        unsigned short flags[2];
    } data;
} FRAME;

typedef union TagHeader
{
    char buffer[10];

    struct
    {
        unsigned char identifier[3];
        unsigned char version[2];
        unsigned char flags;
        unsigned int size;
    } data;
} TAGHEADER;



unsigned int Anti_reverse_byte(unsigned int be_in) {
    unsigned int in = 0ul;
    in = ((be_in >> 24) | ((be_in >> 8) & 0xFF00ul) |
          ((be_in << 8) & 0xFF0000ul) | (be_in << 24));
    return in;
}

unsigned int Reverse_Bytes(unsigned int be_in)
{
    unsigned int out = 0ul, mask = 0x7F000000ul;
    unsigned int in = 0ul;

    in = ((be_in >> 24) | ((be_in >> 8) & 0xFF00ul) |
          ((be_in << 8) & 0xFF0000ul) | (be_in << 24));
    while (mask) {
        out >>= 1;
        out |= (in & mask);
        mask >>= 8;
    }
    return out;
}

void ShowFrame(FRAME frame, unsigned char* content)
{
    printf("frame ID: %s \n", frame.data.frame_ID);
    unsigned int frameSize = Reverse_Bytes(frame.data.size);
    printf("size: %d\n", frameSize);
    printf("content: ");
    for (unsigned int i = 0; i < frameSize; i++) {
        printf("%c", content[i]);
    }
    printf("\n\n");
}

void Show(char* Name_Of_File)
{
    FILE* file;
    file = fopen(Name_Of_File, "rb");
    if (file == NULL)
    {
        printf("Error: file not found\n");
        return;
    }
    fseek(file, 0, SEEK_SET);
    TAGHEADER tag;
    fread(tag.buffer, sizeof(char), 10, file);
    printf("%s\n", Name_Of_File);
    unsigned int tagSize = Reverse_Bytes(tag.data.size);
    while(ftell(file) < tagSize - 10)
    {
        printf("\n\n");
        FRAME frame;
        fread(frame.buffer, sizeof(char), 10, file);
        if (frame.data.frame_ID[0] == '\0' || frame.data.frame_ID[4] != '\0')
            return;
        unsigned char *content;
        unsigned int frameSize = Reverse_Bytes(frame.data.size);
        content = malloc(sizeof(unsigned char) * frameSize);
        fread(content, sizeof(unsigned char), frameSize, file);
        ShowFrame(frame, content);
        free(content);
    }
    fclose(file);
}

void Get(char* Name_Of_File, char* Name_Of_Frame)
{
    FILE* file;
    file = fopen(Name_Of_File, "rb");
    if (file == NULL)
    {
        printf("Error: file not found1\n");
        return;
    }
    fseek(file, 0, SEEK_SET);
    TAGHEADER tag;
    fread(tag.buffer, sizeof(char), 10, file);
    unsigned int tagSize = Reverse_Bytes(tag.data.size);
    while(ftell(file) < tagSize - 10)
    {
        FRAME frame;
        fread(frame.buffer, sizeof(char), 10, file);
        if (frame.data.frame_ID[0] == '\0' || frame.data.frame_ID[4] != '\0')
        {
            printf("Error: frame not found\n\n");
            return;
        }
        unsigned int frameSize = Reverse_Bytes(frame.data.size);
        unsigned char *content;
        content = malloc(sizeof(unsigned char) * frameSize);
        fread(content, sizeof(unsigned char), frameSize, file);
        if (strcmp(Name_Of_Frame, frame.data.frame_ID) == 0)
        {
            ShowFrame(frame, content);
            printf("\n");
            return;
        }
        free(content);
    }
    fclose(file);
}

void Set(char* fileName, char* frameName, char*value)
{
    FILE* file;
    file = fopen(fileName, "rb");
    if (file == NULL)
    {
        printf("Error: file wasn't found\n");
        return;
    }
    fseek(file, 0, SEEK_SET);
    printf("\n", fileName);
    TAGHEADER tag;
    fread(tag.buffer, sizeof(char), 10, file);
    unsigned int tagSize = Reverse_Bytes(tag.data.size);
    unsigned int framePosition;
    FRAME frame;
    unsigned int frameSize;
    while(ftell(file) < tagSize - 10)
    {
        fread(frame.buffer, sizeof(char), 10, file);
        if (frame.data.frame_ID[0] == '\0' || frame.data.frame_ID[4] != '\0') {
            printf("Error: frame not found\n\n");
            return;
        }
        frameSize = Reverse_Bytes(frame.data.size);
        if (strcmp(frameName, frame.data.frame_ID) == 0) {
            framePosition = ftell(file) - 10;
            break;
        }
        unsigned char *content;
        content = malloc(sizeof(unsigned char) * frameSize);
        fread(content, sizeof(unsigned char), frameSize, file);
        free(content);
    }
    FILE* fileCopy;
    fileCopy = fopen("tmp.mp3", "wb");
    fseek(file, 0, SEEK_SET);
    fseek(fileCopy, 0, SEEK_SET);
    unsigned char copy_byte;
    while (!feof(file))
    {
        copy_byte = getc(file);
        putc(copy_byte, fileCopy);
    }
    fclose(file);
    fclose(fileCopy);
    file = fopen(fileName, "wb");
    fileCopy = fopen("tmp.mp3", "rb");
    fseek(file, 0, SEEK_SET);
    fseek(fileCopy, 0, SEEK_SET);
    while(ftell(fileCopy) != framePosition)
    {
        copy_byte = getc(fileCopy);
        putc(copy_byte, file);
    }
    fseek(fileCopy, framePosition + 10 + frameSize, SEEK_SET);
    frame.data.size = Anti_reverse_byte(strlen(value));
    fwrite(frame.buffer, sizeof(char), 10, file);
    fwrite(value, sizeof(char), strlen(value), file);
    while (!feof(fileCopy))
    {
        copy_byte = getc(fileCopy);
        putc(copy_byte, file);
    }
    printf("Set a frame %s: %s\n", frameName, value);
    fclose(file);
    fclose(fileCopy);
    remove("tmp.mp3");
}

int main(int argc, char* argv[])
{
    char* Name_of_the_file;
    char* Name_of_the_frame;
    unsigned char* value;
    if (argc < 1 || argc > 4) {
        printf("%s", "Error: incorrect data entry\n");
        return 0;
    }
    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "--filepath=", 10) == 0) {
            Name_of_the_file = strpbrk(argv[i], "=") + 1;
        }
        else if (strcmp(argv[i], "--show") == 0) {
            Show(Name_of_the_file);
            break;
        }
        else if (strncmp(argv[i], "--get=", 5) == 0) {
            Name_of_the_frame = strpbrk(argv[i], "=") + 1;
            Get(Name_of_the_file, Name_of_the_frame);
            break;
        }
        else if (strncmp(argv[i], "--set=", 5) == 0)
        {
            Name_of_the_frame = strpbrk(argv[i], "=") + 1;
            if (strncmp(argv[3], "--value=", 7) != 0)
            {
                printf("%s", "Error: Incorrect data\n");
                break;
            }
            value = strpbrk(argv[3], "=") + 1;
            Set(Name_of_the_file, Name_of_the_frame, value);
            break;
        }
        else
        {
            printf("%s", "Error: Incorrect data\n");
            return 0;
        }
    }
    return 0;
}