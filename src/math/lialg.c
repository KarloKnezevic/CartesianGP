/*
 * lialg.c
 *
 *  Created on: 19. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "lialg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

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
	m->data = (double **) malloc(rows * sizeof(double*));

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
//                            SETTER
//-----------------------------------------------------------------

void _setSMatrixData(struct matrix *m, double val) {
	_setMatrixData(m, 0, 0, val);
}

void _setMatrixData(struct matrix *m, int i, int j, double val) {
	if (NULL == m) {
		printf("Error: matrix has not been initialised.\n");
		exit(0);
	}

	m->data[i][j] = val;
}

//-----------------------------------------------------------------
//                            GETTER
//-----------------------------------------------------------------

double _getMatrixAsScalar(struct matrix *m) {
	if (NULL == m) {
		printf("Error: matrix has not been initialised.\n");
		return 0;
	}

	//return 1st element
	//if matrix is not 1x1, consider what to return
	return m->data[0][0];
}

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printMatrix(struct matrix *m) {

	if (NULL == m) {
//		printf(
//				"Error: matrix has not been initialised and cannot be printed.\n");
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
		printf("|");
	}

	return;
}

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeMatrix(struct matrix *m) {
	if (m == NULL) {
		printf("Warning: double freeing of matrix prevented.\n");
		return;
	}

	int i;
	for (i = 0; i < m->rows; i++) {
		free(m->data[i]);
	}

	free(m->data);
	free(m);
}

//-----------------------------------------------------------------
//                          MATH
//-----------------------------------------------------------------

struct matrix* _mulWithScalar(struct matrix *m, double scalar) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->data[i][j] *= scalar;
		}
	}

	return m;
}

//-----------------------------------------------------------------
//                          ASSERT
//-----------------------------------------------------------------

void _checkMatrixForNaN(struct matrix *m, double val) {
	if (m == NULL) {
		printf("Error: matrix has not been initialised.\n");
		return;
	}

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (isnan(m->data[i][j]) != 0) {
				m->data[i][j] = 0;
			}
		}
	}
}

void _checkMatrixForInf(struct matrix *m) {
	if (m == NULL) {
		printf("Error: matrix has not been initialised.\n");
		return;
	}

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (isinf(m->data[i][j]) != 0) {
				if (m->data[i][j] > 0) {
					m->data[i][j] = DBL_MAX;
				} else {
					m->data[i][j] = DBL_MIN;
				}

			}
		}
	}
}

void _copyMatrix(struct matrix *mDest, struct matrix *mSrc) {
	for (int i = 0; i < mSrc->rows; i++) {
		for (int j = 0; j < mSrc->cols; j++) {
			mDest->data[i][j] = mSrc->data[i][j];
		}
	}
}

struct matrix *_copyMatrixOf(struct matrix *m) {
	struct matrix *copyOfM = _initialiseMatrix(m->rows, m->cols);
	_copyMatrix(copyOfM, m);
	return copyOfM;
}

