#ifndef FUNCTIONS
#define FUNCTIONS

//структура, которая отвечает за задание фигуры
struct Figure {
    double x_a;
    double y_a;
    double x_b;
    double y_b;
    double x_c;
    double y_c;
    double x_d;
    double y_d;
    double ab;
    double bc;
    double ac;
    double ad;
    double S;
    double P;
};

void Space(struct Figure*);
void Perimeter(struct Figure*);
void Length_of_vector(struct Figure*);

#endif //FUNCTIONS
