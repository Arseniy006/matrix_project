#include "matrix/matrix.h"

int main() {
    Matrix* A = read_matrix("data/A.txt");
    Matrix* B = read_matrix("data/B.txt");
    
    if (!A || !B) {
        fprintf(stderr, "Ошибка загрузки матриц\n");
        return 1;
    }
    
    printf("Матрица A (%dx%d):\n", A->rows, A->cols);
    print_matrix(A);
    
    printf("\nМатрица B (%dx%d):\n", B->rows, B->cols);
    print_matrix(B);
    
    Matrix* C = multiply_matrix(A, B);
    if (!C) {
        fprintf(stderr, "Нельзя умножить матрицы: несовместимые размеры\n");
        free_matrix(A);
        free_matrix(B);
        return 1;
    }
    
    printf("\nРезультат умножения C (%dx%d):\n", C->rows, C->cols);
    print_matrix(C);
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    
    return 0;
}
