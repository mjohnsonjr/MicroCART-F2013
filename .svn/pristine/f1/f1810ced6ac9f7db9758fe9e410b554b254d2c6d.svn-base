#include "matrixmath.h"

//------------------//
// Public Functions //
//------------------//

int MATRIXMATH_multiply(float* matrix_c, float* matrix_a, float* matrix_b, int num_rows, int num_columns) {
	int row;
	int column;
	int i;

	for (row=0; row<num_rows; row=row+1)
	{
		for (column=0; column<num_columns; column=column+1)
		{
			//c[row][column] = 0
			matrix_c[row*num_columns+column] = 0;
			for (i=0; i<num_rows; i=i+1)
			{
				//c[row][column] = c[row][column] + a[row][column] * b[row][column]
				matrix_c[row*num_columns+column] = matrix_c[row*num_columns+column] + matrix_a[row*num_rows+i]*matrix_b[i*num_columns+column];
			}
		}
	}

	return 1;
}

int MATRIXMATH_add(float* matrix_c, float* matrix_a, float* matrix_b, int num_rows, int num_columns) {
	int i;
	int i_max;

	i_max = num_rows*num_columns;
	for (i=0; i<i_max; i=i+1)
	{
		matrix_c[i] = matrix_a[i] + matrix_b[i];
	}

	return 1;
}

int MATRIXMATH_subtract(float* matrix_c, float* matrix_a, float* matrix_b, int num_rows, int num_columns) {
	int i;
	int i_max;

	i_max = num_rows*num_columns;
	for (i=0; i<i_max; i=i+1)
	{
		matrix_c[i] = matrix_a[i] - matrix_b[i];
	}

	return 1;
}

int MATRIXMATH_inverse4x4(float* matrix_out, float* matrix_in) {
	//There's a lot of math here.
	//It's probably not very efficient math either.
	//But it works.
	float det_A;
	float inv_det_A;

	det_A = matrix_in[0]*matrix_in[5]*matrix_in[10]*matrix_in[15]
	      + matrix_in[0]*matrix_in[6]*matrix_in[11]*matrix_in[13]
	      + matrix_in[0]*matrix_in[7]*matrix_in[9]*matrix_in[14]
	      + matrix_in[1]*matrix_in[4]*matrix_in[11]*matrix_in[14]
	      + matrix_in[1]*matrix_in[6]*matrix_in[8]*matrix_in[15]
	      + matrix_in[1]*matrix_in[7]*matrix_in[10]*matrix_in[12]
	      + matrix_in[2]*matrix_in[4]*matrix_in[9]*matrix_in[15]
	      + matrix_in[2]*matrix_in[5]*matrix_in[11]*matrix_in[12]
	      + matrix_in[2]*matrix_in[7]*matrix_in[8]*matrix_in[13]
	      + matrix_in[3]*matrix_in[4]*matrix_in[10]*matrix_in[13]
	      + matrix_in[3]*matrix_in[5]*matrix_in[8]*matrix_in[14]
	      + matrix_in[3]*matrix_in[6]*matrix_in[9]*matrix_in[12]
	      - matrix_in[0]*matrix_in[5]*matrix_in[11]*matrix_in[14]
	      - matrix_in[0]*matrix_in[6]*matrix_in[9]*matrix_in[15]
	      - matrix_in[0]*matrix_in[7]*matrix_in[10]*matrix_in[13]
	      - matrix_in[1]*matrix_in[4]*matrix_in[10]*matrix_in[15]
	      - matrix_in[1]*matrix_in[6]*matrix_in[11]*matrix_in[12]
	      - matrix_in[1]*matrix_in[7]*matrix_in[8]*matrix_in[14]
	      - matrix_in[2]*matrix_in[4]*matrix_in[11]*matrix_in[13]
	      - matrix_in[2]*matrix_in[5]*matrix_in[8]*matrix_in[15]
	      - matrix_in[2]*matrix_in[7]*matrix_in[9]*matrix_in[12]
	      - matrix_in[3]*matrix_in[4]*matrix_in[9]*matrix_in[14]
	      - matrix_in[3]*matrix_in[5]*matrix_in[10]*matrix_in[12]
	      - matrix_in[3]*matrix_in[6]*matrix_in[8]*matrix_in[13];

	inv_det_A = 1/det_A;

	matrix_out[0] = (inv_det_A)*(matrix_in[5]*matrix_in[10]*matrix_in[15]
	                            + matrix_in[6]*matrix_in[11]*matrix_in[13]
	                            + matrix_in[7]*matrix_in[9]*matrix_in[14]
	                            - matrix_in[5]*matrix_in[11]*matrix_in[14]
	                            - matrix_in[6]*matrix_in[9]*matrix_in[15]
	                            - matrix_in[7]*matrix_in[10]*matrix_in[13]);
	matrix_out[1] = (inv_det_A)*(matrix_in[1]*matrix_in[11]*matrix_in[14]
	                            + matrix_in[2]*matrix_in[9]*matrix_in[15]
	                            + matrix_in[3]*matrix_in[10]*matrix_in[13]
	                            - matrix_in[1]*matrix_in[10]*matrix_in[15]
	                            - matrix_in[2]*matrix_in[11]*matrix_in[13]
	                            - matrix_in[3]*matrix_in[9]*matrix_in[14]);
	matrix_out[2] = (inv_det_A)*(matrix_in[1]*matrix_in[6]*matrix_in[15]
	                            + matrix_in[2]*matrix_in[7]*matrix_in[13]
	                            + matrix_in[3]*matrix_in[5]*matrix_in[14]
	                            - matrix_in[1]*matrix_in[7]*matrix_in[14]
	                            - matrix_in[2]*matrix_in[5]*matrix_in[15]
	                            - matrix_in[3]*matrix_in[6]*matrix_in[13]);
	matrix_out[3] = (inv_det_A)*(matrix_in[1]*matrix_in[7]*matrix_in[10]
	                            + matrix_in[2]*matrix_in[5]*matrix_in[11]
	                            + matrix_in[3]*matrix_in[6]*matrix_in[9]
	                            - matrix_in[1]*matrix_in[6]*matrix_in[11]
	                            - matrix_in[2]*matrix_in[7]*matrix_in[9]
	                            - matrix_in[3]*matrix_in[5]*matrix_in[10]);
	matrix_out[4] = (inv_det_A)*(matrix_in[4]*matrix_in[11]*matrix_in[14]
	                            + matrix_in[6]*matrix_in[8]*matrix_in[15]
	                            + matrix_in[7]*matrix_in[10]*matrix_in[12]
	                            - matrix_in[4]*matrix_in[10]*matrix_in[15]
	                            - matrix_in[6]*matrix_in[11]*matrix_in[12]
	                            - matrix_in[7]*matrix_in[8]*matrix_in[14]);
	matrix_out[5] = (inv_det_A)*(matrix_in[0]*matrix_in[10]*matrix_in[15]
	                            + matrix_in[2]*matrix_in[11]*matrix_in[12]
	                            + matrix_in[3]*matrix_in[8]*matrix_in[14]
	                            - matrix_in[0]*matrix_in[11]*matrix_in[14]
	                            - matrix_in[2]*matrix_in[8]*matrix_in[15]
	                            - matrix_in[3]*matrix_in[10]*matrix_in[12]);
	matrix_out[6] = (inv_det_A)*(matrix_in[0]*matrix_in[7]*matrix_in[14]
	                            + matrix_in[2]*matrix_in[4]*matrix_in[15]
	                            + matrix_in[3]*matrix_in[6]*matrix_in[12]
	                            - matrix_in[0]*matrix_in[6]*matrix_in[15]
	                            - matrix_in[2]*matrix_in[7]*matrix_in[12]
	                            - matrix_in[3]*matrix_in[4]*matrix_in[14]);
	matrix_out[7] = (inv_det_A)*(matrix_in[0]*matrix_in[6]*matrix_in[11]
	                            + matrix_in[2]*matrix_in[7]*matrix_in[8]
	                            + matrix_in[3]*matrix_in[4]*matrix_in[10]
	                            - matrix_in[0]*matrix_in[7]*matrix_in[10]
	                            - matrix_in[2]*matrix_in[4]*matrix_in[11]
	                            - matrix_in[3]*matrix_in[6]*matrix_in[8]);
	matrix_out[8] = (inv_det_A)*(matrix_in[4]*matrix_in[9]*matrix_in[15]
	                            + matrix_in[5]*matrix_in[11]*matrix_in[12]
	                            + matrix_in[7]*matrix_in[8]*matrix_in[13]
	                            - matrix_in[4]*matrix_in[11]*matrix_in[13]
	                            - matrix_in[5]*matrix_in[8]*matrix_in[15]
	                            - matrix_in[7]*matrix_in[9]*matrix_in[12]);
	matrix_out[9] = (inv_det_A)*(matrix_in[0]*matrix_in[11]*matrix_in[13]
	                            + matrix_in[1]*matrix_in[8]*matrix_in[15]
	                            + matrix_in[3]*matrix_in[9]*matrix_in[12]
	                            - matrix_in[0]*matrix_in[9]*matrix_in[15]
	                            - matrix_in[1]*matrix_in[11]*matrix_in[12]
	                            - matrix_in[3]*matrix_in[8]*matrix_in[13]);
	matrix_out[10] = (inv_det_A)*(matrix_in[0]*matrix_in[5]*matrix_in[15]
	                            + matrix_in[1]*matrix_in[7]*matrix_in[12]
	                            + matrix_in[3]*matrix_in[4]*matrix_in[13]
	                            - matrix_in[0]*matrix_in[7]*matrix_in[13]
	                            - matrix_in[1]*matrix_in[4]*matrix_in[15]
	                            - matrix_in[3]*matrix_in[5]*matrix_in[12]);
	matrix_out[11] = (inv_det_A)*(matrix_in[0]*matrix_in[7]*matrix_in[9]
	                            + matrix_in[1]*matrix_in[4]*matrix_in[11]
	                            + matrix_in[3]*matrix_in[5]*matrix_in[8]
	                            - matrix_in[0]*matrix_in[5]*matrix_in[11]
	                            - matrix_in[1]*matrix_in[7]*matrix_in[8]
	                            - matrix_in[3]*matrix_in[4]*matrix_in[9]);
	matrix_out[12] = (inv_det_A)*(matrix_in[4]*matrix_in[10]*matrix_in[13]
	                            + matrix_in[5]*matrix_in[8]*matrix_in[14]
	                            + matrix_in[6]*matrix_in[9]*matrix_in[12]
	                            - matrix_in[4]*matrix_in[9]*matrix_in[14]
	                            - matrix_in[5]*matrix_in[10]*matrix_in[12]
	                            - matrix_in[6]*matrix_in[8]*matrix_in[13]);
	matrix_out[13] = (inv_det_A)*(matrix_in[0]*matrix_in[9]*matrix_in[14]
	                            + matrix_in[1]*matrix_in[10]*matrix_in[12]
	                            + matrix_in[2]*matrix_in[8]*matrix_in[13]
	                            - matrix_in[0]*matrix_in[10]*matrix_in[13]
	                            - matrix_in[1]*matrix_in[8]*matrix_in[14]
	                            - matrix_in[2]*matrix_in[9]*matrix_in[12]);
	matrix_out[14] = (inv_det_A)*(matrix_in[0]*matrix_in[6]*matrix_in[13]
	                            + matrix_in[1]*matrix_in[4]*matrix_in[14]
	                            + matrix_in[2]*matrix_in[5]*matrix_in[12]
	                            - matrix_in[0]*matrix_in[5]*matrix_in[14]
	                            - matrix_in[1]*matrix_in[6]*matrix_in[12]
	                            - matrix_in[2]*matrix_in[4]*matrix_in[13]);
	matrix_out[15] = (inv_det_A)*(matrix_in[0]*matrix_in[5]*matrix_in[10]
	                            + matrix_in[1]*matrix_in[6]*matrix_in[8]
	                            + matrix_in[2]*matrix_in[4]*matrix_in[9]
	                            - matrix_in[0]*matrix_in[6]*matrix_in[9]
	                            - matrix_in[1]*matrix_in[4]*matrix_in[10]
	                            - matrix_in[2]*matrix_in[5]*matrix_in[8]);

	return 1;
}

int MATRIXMATH_transpose(float* matrix_out, float* matrix_in, int num_rows, int num_columns) {
	int row;
	int column;

	for (row=0; row<num_rows; row=row+1)
	{
		for (column=0; column<num_columns; column=column+1)
		{
			//out[row][column] = in[column][row];
			matrix_out[row*num_columns+column] = matrix_in[column*num_rows+row];
		}
	}

	return 1;
}
