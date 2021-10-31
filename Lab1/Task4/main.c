#include <stdio.h>

int main() {
    int number1 ;
    int number2;
    printf("%s","Please, enter the number which will be checked: ");
    scanf("%i", &number1);//Считываю десятичное число
    printf("%s","\n");
    printf("%s", (number1 > 23 && 45 > number1) ? "Number is in the gap" : "Number is not in the gap");//Проверяю попадает ли данное число в промежуток
    printf("%s","\n");
    printf("%s","Please, enter the number for bit checking in 8th notation: ");
    scanf("%o", &number2);//Считываю число в восьмеричной системе счисления
    printf("\n%s%i","The fourth bit is: ", (number2 & 268435456) == 268435456 ? 1 : 0 );//Вывожу значение четвертого бита, считая с левого конца числа
    return 0;
}
