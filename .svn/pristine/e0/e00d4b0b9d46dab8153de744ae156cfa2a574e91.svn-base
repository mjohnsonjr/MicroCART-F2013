/*
 * matrix_utils.h
 *
 *  Created on: Mar 30, 2014
 *      Author: Kevin Engel
 */

// Include guard 
#ifndef MATRIX_MATH_H_   
#define MATRIX_MATH_H_

// function declaration
char matrixMultiply(float** output, char outRows, char outCols, float** inputA, char rowsA, char colsA, float** inputB, char rowsB, char colsB);
char matrixAdd(float** output, char outRows, char outCols, float** inputA, char rowsA, char colsA, float** inputB, char rowsB, char colsB);
char matrixSubtract(float** output, char outRows, char outCols, float** inputA, char rowsA, char colsA, float** inputB, char rowsB, char colsB);
char matrixInverse4x4(float** output, char outRows, char outCols, float** input, char inRows, char inCols);
char matrixTranspose(float** output, char outRows, char outCols, float** input, char inRows, char inCols);

void printMatrix(float** matrix, char rows, char cols);
void printArray(float* array, int length);
void fillMatrix(float** matrix, char rows, char cols, int seed);
float** createMatrix(char rows, char cols);
float** createIdentityMatrix(char rows, char cols, float value);
void freeMatrix(float** matrix, char rows, char cols);
char matrixToArray_CMO(float* array, int length, float** matrix, char rows, char cols);
char arrayToMatrix_CMO(float** matrix, char rows, char cols, float* array, int length);  


#endif
