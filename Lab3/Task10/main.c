#include <stdio.h>
#include <string.h>

//Подсчет суммы цифр
int recurs_count(int number) {
    int counter = number % 10;
    return number > 9 ?  number%10 + recurs_count(number/10) :  number;
}
//Удаление пробелов
void DelSpace(char* str, int ind)
{
    int i;
    if ((str[ind]==' ')&&(str[ind+1])==' ')
        DelSpace(str,ind+1);
    for (i = ind; i < strlen(str)-1; i++)
    {
        str[i]=str[i+1];
    }
        str[i]=0;
}

//Task10
int main() {
    char Array[]="123        af   d";
    for (int i=0;i<strlen(Array);i++)
    { if ((Array[i]==' ')&&(Array[i+1]==' '))
        DelSpace(Array,i+1);
    }
    for (int i = 0; i < strlen(Array); ++i) {
        printf("%c", Array[i]);
    }
    printf("\n");
    int number = 15;
    number = recurs_count(number);
    printf("%d", number);
    return 0;
}
