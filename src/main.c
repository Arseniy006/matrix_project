#include <stdio.h>
#include "matrix/matrix.h"

int main() {
    // Загрузка матриц из файлов
    Matrix* A = load_matrix_from_file("../data/A.txt");
    Matrix* B = load_matrix_from_file("../data/B.txt");
    Matrix* C = load_matrix_from_file("../data/C.txt");
    Matrix* D = load_matrix_from_file("../data/D.txt");
    
    if (!A || !B || !C || !D) {
        printf("Ошибка загрузки матриц. Проверьте файлы в папке data/\n");
        return 1;
    }
    
    printf("Матрица A:\n");
    print_matrix(A);
    
    printf("\nМатрица B:\n");
    print_matrix(B);
    
    printf("\nМатрица C:\n");
    print_matrix(C);
    
    printf("\nМатрица D:\n");
    print_matrix(D);
    
    // Вычисление A − Bᵀ × C + D
    Matrix* B_transposed = transpose_matrix(B);
    if (!B_transposed) {
        printf("Ошибка транспонирования B\n");
        return 1;
    }
    
    Matrix* BC = multiply_matrices(B_transposed, C);
    if (!BC) {
        printf("Ошибка умножения Bᵀ × C\n");
        return 1;
    }
    
    Matrix* A_minus_BC = subtract_matrices(A, BC);
    if (!A_minus_BC) {
        printf("Ошибка вычитания A - (Bᵀ × C)\n");
        return 1;
    }
    
    Matrix* result = add_matrices(A_minus_BC, D);
    
    if (result) {
        printf("\nРезультат A − Bᵀ × C + D:\n");
        print_matrix(result);
    } else {
        printf("Ошибка вычисления\n");
    }
    
    // Освобождение памяти
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(B_transposed);
    free_matrix(BC);
    free_matrix(A_minus_BC);
    free_matrix(result);
    
    return 0;
}
