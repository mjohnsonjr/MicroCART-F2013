/*
 * matrix_utils.c
 *
 *  Created on: Mar 30, 2014
 *      Author: Kevin Engel
 */
 
#include "matrix_utils.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
 
/**
 *	multiplies matrices (dot product): 'inputA' * 'inputB' and stores in 'output' matrix
 *	returns 0 if matrices are incorrect sizes
 *	returns 1, otherwise  
 */
char matrixMultiply(float** output, char outRows, char outCols, float** inputA, char rowsA, char colsA, float** inputB, char rowsB, char colsB)
{
	char i = 0;
	char j = 0;
	char k = 0;
	
	float sum = 0;
	
	//cols of A must be same as rows of B, output must reflect this
	if(colsA != rowsB || outRows != rowsA || outCols != colsB)
	{
		return 0;
	}
	else
	{
		// multiplcation and results matrix filled	
		for( i = 0; i < outRows; i++)
		{
			for( j = 0; j < outCols; j++)
			{
				for( k = 0; k < colsA; k++)
				{
					sum = sum + inputA[i][k]*inputB[k][j];
				}
				output[i][j] = sum;
				sum = 0;
			}
		}	
	}
	return 1;
}

/**
 *	adds matrices: 'inputA' + 'inputB' and stores in 'output' matrix
 *	returns 0 if matrices are incorrect sizes
 *	returns 1, otherwise  
 */
char matrixAdd(float** output, char outRows, char outCols, float** inputA, char rowsA, char colsA, float** inputB, char rowsB, char colsB)
{
	char i = 0;
	char j = 0;
		
	//rows and cols for all matrices must be the same, respectively
	if( ! (outRows == rowsA && outRows == rowsB && outCols == colsA && outCols == colsB)) 
	{
		return 0;
	}
	
	//add, fill output matrix	
	for( i = 0; i < outRows; i++){
		for( j = 0; j < outCols; j++){			
			output[i][j] = inputA[i][j] + inputB[i][j];		
		}
	}	
	return 1;
}


/**
 *	subtracts matrices: 'inputA' - 'inputB' and stores in 'output' matrix
 *	returns 0 if matrices are incorrect sizes
 *	returns 1, otherwise  
 */
char matrixSubtract(float** output, char outRows, char outCols, float** inputA, char rowsA, char colsA, float** inputB, char rowsB, char colsB)
{
	char i = 0;
	char j = 0;
		
	//rows and cols for all matrices must be the same, respectively
	if( ! (outRows == rowsA && outRows == rowsB && outCols == colsA && outCols == colsB)) 
	{
		return 0;
	}
	
	//subtract, fill output matrix	
	for( i = 0; i < outRows; i++){
		for( j = 0; j < outCols; j++){			
			output[i][j] = inputA[i][j] - inputB[i][j];		
		}
	}	
	return 1;
}


/**
 * inverts (4x4) matrix 'input' and stores in (4x4) matrix 'output'
 * returns 0 if input or output matrix is not 4x4
 * returns 0 if inverse matrix is impossible to calculate
 *	returns 1, otherwise
 */
char matrixInverse4x4(float** output, char outRows, char outCols, float** input, char inRows, char inCols)
{
    //found code online
    //https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    
    //input and output matrices must be 4x4
    if(! (inRows == inCols && inRows == outRows && inRows == outCols & inRows == 4))
    {
    	return 0;
    }
    
    char arr_length = 16;
    char matrix_rows = 4;
    char matrix_cols = 4;
    
    //input CMO array
    float m[arr_length];
    //output CMO array
    float invOut[arr_length];
    
    //convert matrix input to CMO array
    matrixToArray_CMO(m, arr_length, input, matrix_rows, matrix_cols);
    
    
    double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return 0;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;
        
	//convert inverted CMO array back to matrix for output
	arrayToMatrix_CMO(output, matrix_rows, matrix_cols, invOut, arr_length);
    
    return 1;
}


/**
 * fills 'output' matrix with the transposed data of 'input' matrix
 * returns 0 if matrices are incorrect sizes
 * returns 1, otherwise 
 *
 */
char matrixTranspose(float** output, char outRows, char outCols, float** input, char inRows, char inCols)
{
	char i = 0;
	char j = 0;

	//rows and columns for both matrices must be transposed
	if(inRows != outCols || inCols != outRows)
	{
		return 0;
	}

	//transpose matrix data
	for(i = 0; i < inRows; i++)
	{
		for(j = 0; j < inCols; j++)
		{
			output[j][i] = input[i][j];
		}
	}
	
	return 1;
}

/**
 *	prints a visual representation of matrix of size (rows x cols)
 */
void printMatrix(float** matrix, char rows, char cols)
{
	char i = 0;
	char j = 0;

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			printf("%.4f, ", matrix[i][j]);
			if(j == cols - 1)
			{
				printf("\n");
			}
		}
	}
}

/**
 *	prints a visual representation of array of size length
 */
void printArray(float* array, int length)
{
	char i = 0;

	for(i = 0; i < length; i++)
	{
		printf("%.1f, ", array[i]);
		if(i == length - 1)
		{
			printf("\n");
		}
	}
}

/**
 *	fills matrix of size (rows x cols) with random values determined by seed
 */
void fillMatrix(float** matrix, char rows, char cols, int seed)
{
	srand(seed);
	char i = 0;
	char j = 0;
	
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			matrix[i][j] = rand()%10; //1;
			//*(*(matrix + i) + j) = 1;
		}
	} 
}

/**
 *	allocates memory for a (rows x cols) matrix, initializes all values to 0, and returns the pointer
 */
float** createMatrix(char rows, char cols)
{
	float** matrix;
	char i;
	
	matrix = (float**) calloc(rows, sizeof(float*));
	for(i = 0; i < rows; i++)
	{
		matrix[i] = (float*) calloc(cols, sizeof(float));
	}
	return matrix;
}

/**
 *	creates a matrix with 'value' in the identity matrix pattern
 * matrix should be (n x n) square, but allows for vectors and other non-square matrices
 */
float** createIdentityMatrix(char rows, char cols, float value)
{
	float** matrix;
	char i = 0;
	char j = 0;
	
	matrix = createMatrix(rows,cols);
	
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if(i == j)
			{
				matrix[i][j] = value;
			}	
			else
			{
				matrix[i][j] = 0;
			}
		}
	}
	return matrix;
}


/**
 * frees the memory given to matrix at creation, for when matrix is no longer being used
 * rows are unused, but eliminates chance for mistake
 */
void freeMatrix(float** matrix, char rows, char cols)
{
	char i = 0;
	for(i = 0; i < rows; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

/**
 * converts a (rows x cols) matrix to array[length] in Column-Major Order 
 * returns 0 if array length doesnt match matrix size
 * returns 1 otherwise
 */
char matrixToArray_CMO(float* array, int length, float** matrix, char rows, char cols)
{
	char i = 0;
	char j = 0;
	
	//array must be of length = rows * cols
	if( length != rows*cols)
	{
		return 0;
	}
	
	//convert to array CMO from matrix
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			array[rows*j+i] = matrix[i][j];
		}
	}	
	return 1;
}

/**
 * converts a array[length] in Column-Major Order to a (rows x cols) matrix
 * returns 0 if array length doesnt match matrix size
 * returns 1 otherwise
 */
char arrayToMatrix_CMO(float** matrix, char rows, char cols, float* array, int length)
{
	char i = 0;
	char j = 0;
	
	//array must be of length = rows * cols
	if( length != rows*cols)
	{
		return 0;
	}
	
	//convert to matrix from array CMO
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			matrix[i][j] = array[rows*j+i];
		}
	}	
	return 1;
}


/**
 *
 *
 *
 */
