#include <stdio.h>

int main() {
    //Task3
    int number1, number2, and;
    printf("%s","Please, enter the number1 in 8th notation:");
    scanf("%o", &number1);//Считываю число в восьмеричной системе счисления
    printf("%s%o","You have entered this number:", number1);//Вывожу введенное число
    printf("%s%x%s%x","\nYour number in 16th notation:", number1, ", with shift:", number1<<4);//Вывожу введенное число со сдвигом на 4 бита влево в шестнадатиричной системе счисления
    printf("%s%x%s%x","\nYour number in 16th notation:", number1, ", with not function:", ~number1);//Вывожу введенное число с примененной побитовой операцией отрицания в шестнадатиричной системе счисления
    printf("%s","\nPlease, enter the number1 in 16th notation:");
    scanf("%x", &number2);//Считываю число в шестнадцатиричной системе счисления
    printf("%x", number1 & number2);//Вывожу побитовое и двух чисел
}

