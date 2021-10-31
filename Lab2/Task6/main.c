#include <stdio.h>
#include <malloc.h>

int main() {
    //Task6
    char Array1[5];
    for (int i = 0; i < 5; ++i) {
        scanf("%c", Array1 + i);
         //*(Array1 + i) = getchar();
    }
    for (int i = 0; i < 5; ++i) {
        printf("%c\t", *(Array1 + i));
    }
    char *Array2 = (char*) malloc(5 * sizeof(char));
    Array2[0] = 'H';
    Array2[1] = 'e';
    Array2[2] = 'l';
    Array2[3] = 'l';
    Array2[4] = 'o';
    printf("\n");
    for (int i = 0; i < 5; ++i) {
        printf("%c\t", Array2[i]);
    }
    free(Array2);
    return 0;
}
