#include <stdio.h>
#include <math.h>

int main() {
    //Task2
    double z1, z2, alpha;
    printf("%s", "Please, input alpha: ");
    scanf("%lf", &alpha);//Считываю значение угла alpha в радианах
    z1 = (sin(2*alpha)+sin(5*alpha)-sin(3*alpha))/(cos(alpha)-cos(3*alpha)+cos(5*alpha));
    z2 = tan(3*alpha);
    printf("%s%f%s%s%f","\nz1 = ", z1,"\n", "z2 = ", z2);//Вывожу значения получившихся алгебраических функций
}

