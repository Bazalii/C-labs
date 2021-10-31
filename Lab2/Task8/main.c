#include <stdio.h>
#include <malloc.h>

int main() {
    int size_of_string, string_compare_size, string_copy_size, checker1 = 0, checker2 = 0;
    char *String1, *String2, wanted_symbol;
    printf("%s", "Input the size of string: ");
    scanf("%d", &size_of_string);
    String1 = (char *)malloc((size_of_string+1) * sizeof(char));//Задание строки 1
    String2 = (char *)malloc((size_of_string+1) * sizeof(char));//Задание строки 2
    printf("\nInput the first string: ");
    scanf("%s", String1);
    printf("\nInput the second string: ");
    scanf("%s", String2);
    printf("\nInput the number of symbols to compare: ");
    scanf("%d", &string_compare_size);
    //Сравнение string_compare_size символов строк
    for (int i = 0; i < string_compare_size; ++i) {
        if (String1[i] == String2[i])
            printf("\n%s%d%s", "Symbols number: ", i, " are the same");
        else
            printf("\n%s%d%s", "Symbols number: ", i, " are not the same");
    }
    //Копирование первых string_copy_size сиволов
    printf("\nInput the number of symbols to copy: ");
    scanf("%d", &string_copy_size);
    if (string_copy_size>0){
        for (int i = 0; i < (string_compare_size-1); ++i) {
        String1[i] = String2[i];
    }
    }
    //Поиск первого вхождения указанного символа
    printf("\nInput the symbol to find:");
    getchar();
    scanf("%c", &wanted_symbol);
    checker1 = 0;
    checker2 = 0;
    for (int i = 0; i < size_of_string; ++i) {
        if (String1[i] == wanted_symbol && checker1 == 0){
            printf("\n%s%d%s", "Symbol is ", i, " in the first string");
            checker1 = 1;
        }
        else if (String2[i] == wanted_symbol && checker2 == 0){
            printf("\n%s%d%s", "Symbol is ", i, " in the second string");
            checker2 = 1;
        }
    }
    if (checker1 == 0 && checker2 == 0){
        printf("\nNo matches\n");
    }
    checker1 = 0;
    printf("\n");
    //Поиск в одной строке любого из множества символов, входящих во вторую строку
    for (int i = 0; i < size_of_string; ++i) {
        for (int j = 0; j < size_of_string; ++j) {
            if (String1[i] == String2[j] && checker1 == 0){
                printf("\n%s%c%s", "Symbol: ", String1[i], " is in the first string");
                checker1 = 1;
            }
        }
    }
    printf("\n");
    //Определение длины отрезка одной строки, не содержащего символы второй строки
    checker1 = 0;
    checker2 = 0;
    for (int i = 0; i < size_of_string; ++i) {
        if (String1[i] != String2[i] && checker2 == 0) {
            checker1++;
        }
    }
    printf("\n%s%d", "The size of the part is: ", checker1);
    return 0;
}
