#include <stdio.h>

int main() {
    //Task5
    //Задаю одномерный массив
    int Array[9] = {12, 13, 14, 15, 16, 17, 18, 19, 20};
    //Вывожу элементы массива на экран
    printf("%s\n", "My array is:");

    for (int i = 0; i < 9; ++i) {
        printf("%i\t", Array[i]);
    }
    //Задаю три двумерных массива - в рамках программы являющиеся матрицами
    int Matrix1[2][2]={{1, 1}, {1, 4}};
    int Matrix2[2][2]={{1, 2}, {4, 1}};
    int Matrix_result[2][2]={{0, 0}, {0, 0}};
    printf("\n%s\n", "Resulting_Matrix:");
    //Вывожу получившуюся матрицу
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            Matrix_result[i][j] = Matrix1[i][0]*Matrix2[0][j] + Matrix1[i][1]*Matrix2[1][j];
            printf("%i\t", Matrix_result[i][j]);
        }
        printf("%s", "\n");
    }
    return 0;
}
