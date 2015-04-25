/*
 * test_matrix_utils.c
 *
 *  Created on: Mar 30, 2014
 *      Author: Kevin Engel
 */
 
#include "matrix_utils.h"
#include <stdio.h>

#define a_rows 4
#define a_cols 4
#define b_rows 4
#define b_cols 4
#define c_rows 4
#define c_cols 5
#define arr_length 20

int main()
{	
	/**/
	char i = 0;
	char j = 0;
	
	
	float** a;
	float** b;
	float** c;
	float** d;
	float** e;
	
	float arr[arr_length];
	
	//create a[][] b[][]
	a = createMatrix(a_rows, a_cols);
	b = createMatrix(b_rows, b_cols);
	c = createMatrix(c_rows, c_cols);
	
	/*
	int size = 4;
	float a[size][size];
	float b[size][size];
	*/	
	
	//initialize
	
	fillMatrix(a,a_rows,a_cols,1);
	sleep(1);
	fillMatrix(b,b_rows,b_cols,2);
	
	/*
	a[0][0] = 1; a[0][1] = 0; a[0][2] = -2; 
	a[1][0] = 0; a[1][1] = 3; a[1][2] = -1;
	
	b[0][0] = 0; b[0][1] = 3;  
	b[1][0] = -2; b[1][1] = -1; 
	b[2][0] = 0; b[2][1] = 4;
	*/
	
	/*
	c[0][0] = 1; c[0][1] = 2; c[0][2] = 3; c[0][3] = 4; c[0][4] = 5;
	c[1][0] = 6; c[1][1] = 7; c[1][2] = 8; c[1][3] = 9; c[1][4] = 10;
	c[2][0] = 11; c[2][1] = 12; c[2][2] = 13; c[2][3] = 14; c[2][4] = 15;
	c[3][0] = 16; c[3][1] = 17; c[3][2] = 18; c[3][3] = 19; c[3][4] = 20;
	*/
	
	b[0][0] = 1; b[0][1] = 0; b[0][2] = 0; b[0][3] = 1; 
	b[1][0] = 0; b[1][1] = 2; b[1][2] = 1; b[1][3] = 2; 
	b[2][0] = 2; b[2][1] = 1; b[2][2] = 0; b[2][3] = 1; 
	b[3][0] = 2; b[3][1] = 0; b[3][2] = 1; b[3][3] = 4; 
	
	/*
	printMatrix(a,a_rows,a_cols);
	printf("\n");
	printMatrix(b,b_rows,b_cols);
	printf("\n");
	*/
	
	/*
	printMatrix(c,c_rows,c_cols);
	printf("\n");
	*/
	
	//test multiply - checked
	/*
	printf("%d\n", matrixMultiply(c,c_rows,c_cols,a,a_rows,a_cols,b,b_rows,b_cols));
	printMatrix(c,c_rows,c_cols);
	printf("\n");
	*/
	 
	//test add - checked
	/*
	printf("%d\n", matrixAdd(c,c_rows,c_cols,a,a_rows,a_cols,b,b_rows,b_cols));
	printMatrix(c,c_rows,c_cols);
	printf("\n");
	*/
	
	//test subtract - checked
	/*
	printf("%d\n", matrixSubtract(c,c_rows,c_cols,a,a_rows,a_cols,b,b_rows,b_cols));
	printMatrix(c,c_rows,c_cols);
	printf("\n");
	*/
	
	//test transpose - checked
	/*
	printf("%d\n", matrixTranspose(a,a_rows,a_cols,b,b_rows,b_cols));
	printMatrix(a,a_rows,a_cols);
	printf("\n");
	*/
	
	//test identity matrix - checked
	/*
	d = createIdentityMatrix(5,5,.3);
	printMatrix(d,5,5);
	printf("\n");
	*/
	
	//test matrix to CMO array conversion - checked
	/*
	matrixToArray_CMO(arr, arr_length, c, c_rows, c_cols);
	printArray(arr, arr_length);
	printf("\n");
	*/
	
	//test CMO array to matrix conersion - checked
	/*
	arrayToMatrix_CMO(c, c_rows, c_cols, arr, arr_length);
	printMatrix(c,c_rows,c_cols);
	printf("\n");
	*/
	
	//test matrix inverse 4x4 - checked
	/*
	printf("success: %d\n", matrixInverse4x4(a, a_rows, a_cols, b, b_rows, b_cols));
	printMatrix(a,a_rows,a_cols);
	printf("\n");
	*/

	//test free matrix
	/*
	printf("testing freeMatrix...this should not seg fault\n");
	int counter = 0;
	while(1)
	{
		printf("%d\n", counter);
		counter++;
		e = createMatrix(5,8);
		usleep(10);
		freeMatrix(e,5,8);
	}
	*/
}


