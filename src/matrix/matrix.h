#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "../../include/config.h"

/**
 * @brief Структура матрицы
 */
typedef struct {
    int rows;     ///< Количество строк
    int cols;     ///< Количество столбцов
    MATRIX_TYPE** data;  ///< Двумерный массив данных
} Matrix;

// Основные функции
Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix* matrix);
Matrix* load_matrix_from_file(const char* filename);
void print_matrix(const Matrix* matrix);

// Операции с матрицами
Matrix* add_matrices(const Matrix* A, const Matrix* B);
Matrix* subtract_matrices(const Matrix* A, const Matrix* B);
Matrix* multiply_matrices(const Matrix* A, const Matrix* B);
Matrix* transpose_matrix(const Matrix* matrix);

#endif // MATRIX_H
