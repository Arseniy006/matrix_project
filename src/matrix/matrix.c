#include "../matrix/matrix.h"
#include <string.h>

// Создание матрицы
Matrix* create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (!matrix) return NULL;
    
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (MATRIX_TYPE**)malloc(rows * sizeof(MATRIX_TYPE*));
    
    if (!matrix->data) {
        free(matrix);
        return NULL;
    }
    
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (MATRIX_TYPE*)malloc(cols * sizeof(MATRIX_TYPE));
        if (!matrix->data[i]) {
            for (int j = 0; j < i; j++) free(matrix->data[j]);
            free(matrix->data);
            free(matrix);
            return NULL;
        }
    }
    
    return matrix;
}

// Освобождение памяти
void free_matrix(Matrix* matrix) {
    if (!matrix) return;
    
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// Загрузка из файла
Matrix* load_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    int rows, cols;
    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        fclose(file);
        return NULL;
    }
    
    Matrix* matrix = create_matrix(rows, cols);
    if (!matrix) {
        fclose(file);
        return NULL;
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, "%lf", &matrix->data[i][j]) != 1) {
                fclose(file);
                free_matrix(matrix);
                return NULL;
            }
        }
    }
    
    fclose(file);
    return matrix;
}

// Вывод матрицы
void print_matrix(const Matrix* matrix) {
    if (!matrix) {
        printf("Matrix is NULL\n");
        return;
    }
    
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%8.2f ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

// Сложение матриц
Matrix* add_matrices(const Matrix* A, const Matrix* B) {
    if (!A || !B || A->rows != B->rows || A->cols != B->cols) return NULL;
    
    Matrix* result = create_matrix(A->rows, A->cols);
    if (!result) return NULL;
    
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            result->data[i][j] = A->data[i][j] + B->data[i][j];
        }
    }
    
    return result;
}

// Вычитание матриц (новая функция для вашего варианта)
Matrix* subtract_matrices(const Matrix* A, const Matrix* B) {
    if (!A || !B || A->rows != B->rows || A->cols != B->cols) return NULL;
    
    Matrix* result = create_matrix(A->rows, A->cols);
    if (!result) return NULL;
    
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            result->data[i][j] = A->data[i][j] - B->data[i][j];
        }
    }
    
    return result;
}

// Умножение матриц
Matrix* multiply_matrices(const Matrix* A, const Matrix* B) {
    if (!A || !B || A->cols != B->rows) return NULL;
    
    Matrix* result = create_matrix(A->rows, B->cols);
    if (!result) return NULL;
    
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < A->cols; k++) {
                result->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }
    
    return result;
}

// Транспонирование матрицы
Matrix* transpose_matrix(const Matrix* matrix) {
    if (!matrix) return NULL;
    
    Matrix* result = create_matrix(matrix->cols, matrix->rows);
    if (!result) return NULL;
    
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[j][i] = matrix->data[i][j];
        }
    }
    
    return result;
}
