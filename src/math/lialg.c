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
#include "../constants/constants.h"

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

		if (i < m->rows - 1) {
			printf("\n");
		}

	}

	return;
}

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeMatrix(struct matrix *m) {
	if (m == NULL) {
		//printf("Warning: double freeing of matrix prevented.\n");
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

double _zerro_div(double a, double b) {
	if (fabs(b) < EPSILON && fabs(a) < EPSILON) {
		return 1;
	} else if (fabs(b) < EPSILON) {
		return a > 0 ? DBL_MAX : DBL_MIN;
	}

	return a / b;
}

double _max_(struct matrix *m) {
	double max = m->data[0][0];

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (m->data[i][j] > max) {
				max = m->data[i][j];
			}
		}
	}

	return max;
}

double _min_(struct matrix *m) {
	double min = m->data[0][0];

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (m->data[i][j] < min) {
				min = m->data[i][j];
			}
		}
	}

	return min;
}

struct matrix* _mulWithScalar(struct matrix *m, double scalar) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->data[i][j] *= scalar;
		}
	}

	return m;
}

struct matrix* _sumElements(struct matrix *m1, const double *factors,
		const double amplitude) {
	double sum = 0.0;
	for (int i = 0; i < m1->cols; i++) {
		sum += m1->data[0][i];
	}

	sum *= amplitude;

	return _initialiseMatrixFromScalar(sum);
}

struct matrix* _add(struct matrix *m1, struct matrix *m2, const double *factors,
		const double amplitude) {
	mtype t_m1 = _getMatrixType(m1);
	mtype t_m2 = _getMatrixType(m2);

	struct matrix *_m;

	if (SCALAR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromScalar(m1->data[0][0] + m2->data[0][0]);
	} else if (SCALAR == t_m1 && VECTOR == t_m2) {
		_m = _initialiseMatrixFromArray(m2->rows, m2->cols, m2->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] += m1->data[0][0];
		}
	} else if (VECTOR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromArray(m1->rows, m1->cols, m1->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] += m2->data[0][0];
		}
	} else {
		struct matrix *first = m1->cols > m2->cols ? m1 : m2;
		struct matrix *second = first == m1 ? m2 : m1;

		_m = _initialiseMatrixFromArray(first->rows, first->cols,
				first->data[0]);
		for (int i = 0; i < second->cols; i++) {
			_m->data[0][i] += second->data[0][i];
		}
	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _sub(struct matrix *m1, struct matrix *m2, const double *factors,
		const double amplitude) {
	mtype t_m1 = _getMatrixType(m1);
	mtype t_m2 = _getMatrixType(m2);

	struct matrix *_m;

	if (SCALAR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromScalar(m1->data[0][0] - m2->data[0][0]);
	} else if (SCALAR == t_m1 && VECTOR == t_m2) {
		_m = _initialiseMatrixFromArray(m2->rows, m2->cols, m2->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] -= m1->data[0][0];
		}
	} else if (VECTOR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromArray(m1->rows, m1->cols, m1->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] -= m2->data[0][0];
		}
	} else {
		struct matrix *first = m1->cols > m2->cols ? m1 : m2;
		struct matrix *second = first == m1 ? m2 : m1;

		_m = _initialiseMatrixFromArray(first->rows, first->cols,
				first->data[0]);
		for (int i = 0; i < second->cols; i++) {
			_m->data[0][i] -= second->data[0][i];
		}
	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _div(struct matrix *m1, struct matrix *m2, const double *factors,
		const double amplitude) {
	mtype t_m1 = _getMatrixType(m1);
	mtype t_m2 = _getMatrixType(m2);

	struct matrix *_m;

	if (SCALAR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromScalar(
				_zerro_div(m1->data[0][0], m2->data[0][0]));
	} else if (SCALAR == t_m1 && VECTOR == t_m2) {
		_m = _initialiseMatrixFromArray(m2->rows, m2->cols, m2->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] = _zerro_div(_m->data[0][i], m1->data[0][0]);
		}
	} else if (VECTOR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromArray(m1->rows, m1->cols, m1->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] = _zerro_div(_m->data[0][i], m2->data[0][0]);
		}
	} else {
		struct matrix *first = m1->cols > m2->cols ? m1 : m2;
		struct matrix *second = first == m1 ? m2 : m1;

		struct matrix *h = _initialiseMatrixFromArray(first->rows, first->cols,
				first->data[0]);
		int i = 0;
		for (i = 0; i < second->cols; i++) {
			h->data[0][i] = _zerro_div(h->data[0][i], second->data[0][i]);
		}

		//invert non divided values
		for (; i < h->cols; i++) {
			h->data[0][i] = _zerro_div(1.0, h->data[0][i]);
		}

		_m = _sumElements(h, factors, amplitude);
		_freeMatrix(h);

	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _mul(struct matrix *m1, struct matrix *m2, const double *factors,
		const double amplitude) {
	mtype t_m1 = _getMatrixType(m1);
	mtype t_m2 = _getMatrixType(m2);

	struct matrix *_m;

	if (SCALAR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromScalar(m1->data[0][0] * m2->data[0][0]);
	} else if (SCALAR == t_m1 && VECTOR == t_m2) {
		_m = _initialiseMatrixFromArray(m2->rows, m2->cols, m2->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] *= m1->data[0][0];
		}
	} else if (VECTOR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromArray(m1->rows, m1->cols, m1->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] *= m2->data[0][0];
		}
	} else {
		struct matrix *first = m1->cols > m2->cols ? m1 : m2;
		struct matrix *second = first == m1 ? m2 : m1;

		struct matrix *h = _initialiseMatrixFromArray(first->rows, first->cols,
				first->data[0]);
		for (int i = 0; i < second->cols; i++) {
			h->data[0][i] *= second->data[0][i];
		}

		_m = _sumElements(h, factors, amplitude);
		_freeMatrix(h);

	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _abs(struct matrix *m1, const double *factors,
		const double amplitude) {
	struct matrix *_m = _mul(m1, m1, factors, amplitude);
	//this is 1x1, but for safety
	for (int i = 0; i < _m->cols; i++) {
		_m->data[0][i] = sqrt(_m->data[0][i]);
	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _sqrt(struct matrix *m1, const double *factors,
		const double amplitude) {
	struct matrix *_m = _initialiseMatrixFromArray(m1->rows, m1->cols,
			m1->data[0]);
	for (int i = 0; i < m1->cols; i++) {
		_m->data[0][i] = sqrt(fabs(_m->data[0][i]));
	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

double _sec_pow(double a, double b) {
	double res = fabs(a);
	res = pow(a, b);

	return a > 0 ? res : -1*res;
}

struct matrix* _pow(struct matrix *m1, struct matrix *m2, const double *factors,
		const double amplitude) {
	mtype t_m1 = _getMatrixType(m1);
	mtype t_m2 = _getMatrixType(m2);

	struct matrix *_m;

	if (SCALAR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromScalar(pow(m1->data[0][0], m2->data[0][0]));
	} else if (SCALAR == t_m1 && VECTOR == t_m2) {
		_m = _initialiseMatrixFromArray(m2->rows, m2->cols, m2->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] = _sec_pow(_m->data[0][i], m1->data[0][0]);
		}
	} else if (VECTOR == t_m1 && SCALAR == t_m2) {
		_m = _initialiseMatrixFromArray(m1->rows, m1->cols, m1->data[0]);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] = _sec_pow(_m->data[0][i], m2->data[0][0]);
		}
	} else {
		struct matrix *first = m1->cols > m2->cols ? m1 : m2;
		struct matrix *second = first == m1 ? m2 : m1;

		_m = _initialiseMatrixFromArray(first->rows, first->cols,
				first->data[0]);
		second = _abs(second, factors, amplitude);
		for (int i = 0; i < _m->cols; i++) {
			_m->data[0][i] = _sec_pow(_m->data[0][i], second->data[0][0]);
		}

		_freeMatrix(second);
	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _powInt(struct matrix *m1, struct matrix *m2,
		const double *factors, const double amplitude) {
	return _pow(m1, m2, factors, amplitude);
}

struct matrix* _sin(struct matrix *m1, const double *factors,
		const double amplitude) {
	struct matrix *_m = _copyMatrixOf(m1);
	for (int i = 0; i < _m->cols; i++) {
		_m->data[0][i] = sin(_m->data[0][i]);
	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _tan(struct matrix *m1, const double *factors,
		const double amplitude) {
	struct matrix *_m = _copyMatrixOf(m1);
	for (int i = 0; i < _m->cols; i++) {
		//singularities problem
		double _cos = cos(_m->data[0][i]);
		if (fabs(_cos) < EPSILON) {
			double _sin = sin(_m->data[0][i]);
			_m->data[0][i] = (_sin * _cos) > 0 ? DBL_MAX : DBL_MIN;
		} else {
			_m->data[0][i] = tan(_m->data[0][i]);
		}

	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _cos(struct matrix *m1, const double *factors,
		const double amplitude) {
	struct matrix *_m = _copyMatrixOf(m1);
	for (int i = 0; i < _m->cols; i++) {
		_m->data[0][i] = cos(_m->data[0][i]);
	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _tanh(struct matrix *m1, const double *factors,
		const double amplitude) {
	struct matrix *_m = _copyMatrixOf(m1);
	for (int i = 0; i < _m->cols; i++) {
		//singularities problem
		if (fabs(_m->data[0][i]) > EPSILON) {
			//if too large
			if (fabs(_m->data[0][i]) > log(DBL_MAX)) {
				_m->data[0][i] = _m->data[0][i] > 0 ? 1 : -1;
			} else {
				_m->data[0][i] = tanh(_m->data[0][i]);
			}
		} else {
			_m->data[0][i] = tanh(_m->data[0][i]);
		}

	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _exp(struct matrix *m1, const double *factors,
		const double amplitude) {
	struct matrix *_m = _copyMatrixOf(m1);
	for (int i = 0; i < _m->cols; i++) {

		if (fabs(_m->data[0][i]) > log(DBL_MAX)) {
			_m->data[0][i] = _m->data[0][i] > 0 ? DBL_MAX : DBL_MIN;
		} else {
			_m->data[0][i] = exp(_m->data[0][i]);
		}

	}

	_mulWithScalar(_m, amplitude);

	return _m;
}

struct matrix* _gt(struct matrix *m1, struct matrix *m2, const double *factors,
		const double amplitude) {
	mtype t_m1 = _getMatrixType(m1);
	mtype t_m2 = _getMatrixType(m2);

	double x1 =
			t_m1 == SCALAR ?
					m1->data[0][0] : (_abs(m1, factors, amplitude))->data[0][0];
	double x2 =
			t_m2 == SCALAR ?
					m2->data[0][0] : (_abs(m2, factors, amplitude))->data[0][0];

	int res = x1 > x2 ? 1 : (x1 < x2 ? -1 : 0);

	return _mulWithScalar(_initialiseMatrixFromScalar(res), amplitude);
}

struct matrix* _lt(struct matrix *m1, struct matrix *m2, const double *factors,
		const double amplitude) {
	return _gt(m2, m1, factors, amplitude);
}

struct matrix* _max(struct matrix *m1, const double *factors,
		const double amplitude) {
	return _initialiseMatrixFromScalar(_max_(m1));
}

struct matrix* _max2(struct matrix *m1, struct matrix *m2,
		const double *factors, const double amplitude) {
	double first = _max_(m1);
	double second = _max_(m2);

	double res = first > second ? first : second;
	return _initialiseMatrixFromScalar(res);
}

struct matrix* _min(struct matrix *m1, const double *factors,
		const double amplitude) {
	double min = m1->data[0][0];

	for (int i = 0; i < m1->rows; i++) {
		for (int j = 0; j < m1->cols; j++) {
			if (m1->data[i][j] < min) {
				min = m1->data[i][j];
			}
		}
	}

	return _initialiseMatrixFromScalar(min);
}

struct matrix* _min2(struct matrix *m1, struct matrix *m2,
		const double *factors, const double amplitude) {
	double first = _min_(m1);
	double second = _min_(m2);

	double res = first < second ? first : second;
	return _initialiseMatrixFromScalar(res);
}

//-----------------------------------------------------------------
//                          STAT
//-----------------------------------------------------------------

struct matrix* _arithmetic_mean(struct matrix *m1, const double *factors,
		const double amplitude) {
	struct matrix *_m = _sumElements(m1, factors, amplitude);
	_m->data[0][0] /= m1->cols;

	return _m;
}

struct matrix* _med(struct matrix *m1, const double *factors,
		const double amplitude) {
	return NULL;
}

struct matrix* _standard_deviation(struct matrix *m1, const double *factors,
		const double amplitude) {
	struct matrix *_m = _arithmetic_mean(m1, factors, amplitude);
	double stdev = 0.0;
	double avg = _m->data[0][0];
	for (int i = 0; i < m1->cols; i++) {
		stdev += (m1->data[0][0] - avg) * (m1->data[0][0] - avg);
	}

	stdev /= m1->cols;
	stdev = sqrt(stdev);
	_m->data[0][0] = stdev;

	return _m;
}

//-----------------------------------------------------------------
//                          ASSERT
//-----------------------------------------------------------------

mtype _getMatrixType(struct matrix *m) {
	if (NULL == m) {
		return NONE;
	} else if (m->cols == 1 && m->rows == 1) {
		return SCALAR;
	} else if (m->rows == 1 && m->cols > 1) {
		return VECTOR;
	} else if (m->rows > 1 && m->cols > 1) {
		//because of algorithms
		return MATRIX;
	}

	return NONE;
}

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

