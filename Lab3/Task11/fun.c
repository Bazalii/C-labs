#include "init.h"
#include <math.h>
//Вычисление длины вектора
void Length_of_vector(struct Figure* obj) {
    obj->ab = (pow(pow(obj->x_a - obj->x_b, 2) + pow(obj->y_a - obj->y_b, 2), 0.5));
    obj->bc = (pow(pow(obj->x_b - obj->x_c, 2) + pow(obj->y_b - obj->y_c, 2), 0.5));
    obj->ac = (pow(pow(obj->x_a - obj->x_c, 2) + pow(obj->y_a - obj->y_c, 2), 0.5));
    obj->ad = (pow(pow(obj->x_a - obj->x_d, 2) + pow(obj->y_a - obj->y_d, 2), 0.5));
}
//Вычисление площади
void Space(struct Figure *obj) {
    obj->S = (obj->x_b-obj->x_a)*(obj->x_c-obj->x_a) + (obj->y_b-obj->y_a)*(obj->y_c-obj->y_a);
}
//Вычисление периметра
void Perimeter(struct Figure *obj) {
    obj->P = obj->ab + obj->bc + obj->ac + obj->ad;
}

