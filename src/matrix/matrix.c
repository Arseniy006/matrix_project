#include "matrix/matrix.h"

Matrix* create_matrix(int rows, int cols) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (MATRIX_TYPE**)malloc(rows * sizeof(MATRIX_TYPE*));
    
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (MATRIX_TYPE*)malloc(cols * sizeof(MATRIX_TYPE));
    }
    return matrix;
}

void free_matrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

Matrix* read_matrix(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    int rows = 0, cols = 0;
    char line[1024];
    
    // Подсчет строк и столбцов
    while (fgets(line, sizeof(line), file)) {
        rows++;
        if (rows == 1) {
            const char* token = strtok(line, " \t\n");
            while (token) {
                cols++;
                token = strtok(NULL, " \t\n");
            }
        }
    }
    
    rewind(file);
    Matrix* matrix = create_matrix(rows, cols);
    
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

Matrix* multiply_matrix(const Matrix* a, const Matrix* b) {
    if (a->cols != b->rows) return NULL;
    
    Matrix* result = create_matrix(a->rows, b->cols);
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < a->cols; k++) {
                result->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    
    return result;
}

void print_matrix(const Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%8.2f", matrix->data[i][j]);
        }
        printf("\n");
    }
}
