#ifndef MATRIX_H
#define MATRIX_H

#include "config.h"

typedef struct {
    int rows;
    int cols;
    MATRIX_TYPE** data;
} Matrix;

Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix* matrix);
Matrix* read_matrix(const char* filename);
void print_matrix(const Matrix* matrix);
Matrix* multiply_matrix(const Matrix* a, const Matrix* b);

#endif
