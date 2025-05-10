#include <CUnit/Basic.h>
#include "../../include/matrix/matrix.h"

void test_matrix_creation(void) {
    Matrix* m = create_matrix(2, 3);
    CU_ASSERT_PTR_NOT_NULL(m);
    CU_ASSERT_EQUAL(m->rows, 2);
    CU_ASSERT_EQUAL(m->cols, 3);
    free_matrix(m);
}

void test_matrix_multiplication(void) {
    Matrix* A = create_matrix(2, 3);
    A->data[0][0] = 1; A->data[0][1] = 2; A->data[0][2] = 3;
    A->data[1][0] = 4; A->data[1][1] = 5; A->data[1][2] = 6;
    
    Matrix* B = create_matrix(3, 2);
    B->data[0][0] = 7; B->data[0][1] = 8;
    B->data[1][0] = 9; B->data[1][1] = 10;
    B->data[2][0] = 11; B->data[2][1] = 12;
    
    Matrix* C = multiply_matrix(A, B);
    CU_ASSERT_PTR_NOT_NULL(C);
    CU_ASSERT_DOUBLE_EQUAL(C->data[0][0], 58.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(C->data[0][1], 64.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(C->data[1][0], 139.0, 0.001);
    CU_ASSERT_DOUBLE_EQUAL(C->data[1][1], 154.0, 0.001);
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

int main() {
    CU_initialize_registry();
    
    CU_pSuite suite = CU_add_suite("Matrix Suite", NULL, NULL);
    CU_add_test(suite, "test_matrix_creation", test_matrix_creation);
    CU_add_test(suite, "test_matrix_multiplication", test_matrix_multiplication);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return 0;
}
