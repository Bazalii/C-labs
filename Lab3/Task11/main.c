#include <stdio.h>
#include "init.h"

int main() {
    struct Figure Parallelogram;
    int a;
    scanf("%lf", &Parallelogram.x_a);
    scanf("%lf", &Parallelogram.y_a);
    scanf("%lf", &Parallelogram.x_b);
    scanf("%lf", &Parallelogram.y_b);
    scanf("%lf", &Parallelogram.x_c);
    scanf("%lf", &Parallelogram.y_c);
    scanf("%lf", &Parallelogram.x_d);
    scanf("%lf", &Parallelogram.y_d);
    Length_of_vector(&Parallelogram);
    Space(&Parallelogram);
    Perimeter(&Parallelogram);
    printf_s("P = %lf\n", Parallelogram.P);
    printf_s("S = %lf\n", Parallelogram.S);
    return 0;
}
