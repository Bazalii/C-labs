#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

 enum Types_of_cars {usual,big,bus,sport,military};
 struct circle{int r;};
 union Registration{//Задание объединения
    struct Condition{//Задание структуры
        unsigned char Ready : 1;
        unsigned char Little_toner : 1;
        unsigned char Drum_damaged : 1;
        unsigned char Paper_in : 1;
    };
    unsigned Input_condition;
 };


 typedef union Registration Register;

int main() {
    //Task7
    union Registration reg;
    struct circle main;
    enum Types_of_cars check = bus;
    double length;
    printf("%d\n", check);
    main.r = 10;
    length = M_PI * main.r;//Вычисление длины окружности
    printf("\n%lf", length);
    printf("\n\n%s", "Please, input condition: ");
    scanf("%x", &reg.Input_condition);//Считывание "состояния" и его вывод
    printf("\n%s%d", "Ready: ", reg.Ready);
    printf("\n%s%d", "Not enough toner: ", reg.Little_toner);
    printf("\n%s%d", "Drum damaged: ", reg.Drum_damaged);
    printf("\n%s%d", "Paper in: ", reg.Paper_in);
    return 0;
}

