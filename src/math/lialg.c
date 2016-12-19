/*
 * lialg.c
 *
 *  Created on: 19. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "lialg.h"
#include <stdio.h>
#include "stdlib.h"

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct matrix *_initialiseMatrixFromArray(int rows, int cols, double *array) {

	struct matrix *m = _initialiseMatrix(rows, cols);

	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			m->data[i][j] = array[i * j + j];
		}
	}

	return m;
}

struct matrix *_initialiseVectorFromArray(int dim, double *array) {
	return _initialiseMatrixFromArray(1, dim, array);
}

struct matrix *_initialiseMatrixFromScalar(double scalar) {
	struct matrix *m = _initialiseMatrix(1, 1);
	m->data[0][0] = scalar;

	return m;
}

struct matrix *_initialiseMatrix(int rows, int cols) {
	if (rows < 1 || cols < 1) {
		printf("Error: matrix dimensions error. \nTerminating.\n);");
		exit(0);
	}

	int i, j;
	struct matrix *m = (struct matrix*) malloc(sizeof(struct matrix));
	m->rows = rows;
	m->cols = cols;

	//rows
	m->data = (double **) malloc(rows * sizeof(double));

	//cols
	for (i = 0; i < rows; i++) {
		m->data[i] = (double *) malloc(cols * sizeof(double));
		for (j = 0; j < cols; j++) {
			m->data[i][j] = 0.0;
		}
	}

	return m;
}

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printMatrix(struct matrix *m) {

	if (NULL == m) {
		printf(
				"Error: matrix has not been initialised and cannot be printed.\n");
		return;
	}

	int i, j;

	for (i = 0; i < m->rows; i++) {
		printf("|");
		for (j = 0; j < m->cols; j++) {

			if (j != 0) {
				printf(" ");
			}

			printf("%.3lf", m->data[i][j]);
		}
		printf("|\n");
	}

	return;
}

