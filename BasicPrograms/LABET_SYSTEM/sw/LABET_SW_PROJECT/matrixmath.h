#ifndef MATRIXMATH_H
#define MATRIXMATH_H

//------------------//
// Public Functions //
//------------------//

/** @brief Multiplies two matrices together.
  * @details c = a*b
  * @param[out] matrix_c
  * @param[in] matrix_a
  * @param[in] matrix_b
  * @param[in] num_rows Number of rows in the output matrix.
  * @param[in] num_columns Number of columns in the output matrix.
  * @return Always 1;
  */
extern int MATRIXMATH_multiply(float* matrix_c, float* matrix_a, float* matrix_b, int num_rows, int num_columns);

/** @brief Adds two matrices together.
  * @details c = a+b
  * @param[out] matrix_c
  * @param[in] matrix_a
  * @param[in] matrix_b
  * @param[in] num_rows Number of rows in the output matrix.
  * @param[in] num_columns Number of columns in the output matrix.
  * @return Always 1;
  */
extern int MATRIXMATH_add(float* matrix_c, float* matrix_a, float* matrix_b, int num_rows, int num_columns);

/** @brief Subtracts one matrix from another.
  * @details c = a-b
  * @param[out] matrix_c
  * @param[in] matrix_a
  * @param[in] matrix_b
  * @param[in] num_rows Number of rows in the output matrix.
  * @param[in] num_columns Number of columns in the output matrix.
  * @return Always 1;
  */
extern int MATRIXMATH_subtract(float* matrix_c, float* matrix_a, float* matrix_b, int num_rows, int num_columns);

/** @brief Calculates the inverse of a 4x4 matrix.
  * @param[out] matrix_out
  * @param[in] matrix_in
  * @param[in] num_rows Number of rows in the output matrix.
  * @param[in] num_columns Number of columns in the output matrix.
  * @return Always 1;
  */
extern int MATRIXMATH_inverse4x4(float* matrix_out, float* matrix_in);

/** @brief Transposes a matrix .
  * @details out = in'
  * @param[out] matrix_out
  * @param[in] matrix_in
  * @param[in] num_rows Number of rows in the output matrix.
  * @param[in] num_columns Number of columns in the output matrix.
  * @return Always 1;
  */
extern int MATRIXMATH_transpose(float* matrix_out, float* matrix_in, int num_rows, int num_columns);

#endif // MATRIXMATH_H
