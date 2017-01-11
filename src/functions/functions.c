/*
 * functions.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "functions.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//-----------------------------------------------------------------
//                           FACTORY
//-----------------------------------------------------------------

struct function *_init(const char *functionName,
		struct matrix *(*function)(const int numInputs, struct matrix **inputs,
				const double *connectionWeights), int args) {

	struct function *object = (struct function*) malloc(
			sizeof(struct function));

	object->mFunction = function;
	object->args = args;
	strncpy(object->functionName, functionName, FUNCTIONNAMELENGTH);

	return object;
}

//-----------------------------------------------------------------
//                           WRAPPER
//-----------------------------------------------------------------

struct function *getFunction(char const *functionName) {

	// VECTOR FUNCTIONS

	if (strncmp(functionName, "head", FUNCTIONNAMELENGTH) == 0) {
		return _init("head", _head, 1);
	} else if (strncmp(functionName, "last", FUNCTIONNAMELENGTH) == 0) {
		return _init("last", _last, 1);
	} else if (strncmp(functionName, "length", FUNCTIONNAMELENGTH) == 0) {
		return _init("length", _length, 1);
	} else if (strncmp(functionName, "tail", FUNCTIONNAMELENGTH) == 0) {
		return _init("tail", _tail, 1);
	} else if (strncmp(functionName, "diff", FUNCTIONNAMELENGTH) == 0) {
		return _init("diff", _diff, 1);
	} else if (strncmp(functionName, "avgdiff", FUNCTIONNAMELENGTH) == 0) {
		return _init("avgdiff", _avgdiff, 1);
	} else if (strncmp(functionName, "rotate", FUNCTIONNAMELENGTH) == 0) {
		return _init("rotate", _rotate, 1);
	} else if (strncmp(functionName, "reverse", FUNCTIONNAMELENGTH) == 0) {
		return _init("reverse", _reverse, 1);
	} else if (strncmp(functionName, "pushback", FUNCTIONNAMELENGTH) == 0) {
		return _init("pushback", _pushback, 2);
	} else if (strncmp(functionName, "pushfront", FUNCTIONNAMELENGTH) == 0) {
		return _init("pushfront", _pushfront, 2);
	} else if (strncmp(functionName, "set", FUNCTIONNAMELENGTH) == 0) {
		return _init("set", _set, 2);
	} else if (strncmp(functionName, "sum", FUNCTIONNAMELENGTH) == 0) {
		return _init("sum", _sum, 1);
	}

	// MATH

	else if (strncmp(functionName, "madd", FUNCTIONNAMELENGTH) == 0) {
		return _init("madd", _madd, 2);
	} else if (strncmp(functionName, "msub", FUNCTIONNAMELENGTH) == 0) {
		return _init("msub", _msub, 2);
	} else if (strncmp(functionName, "mmul", FUNCTIONNAMELENGTH) == 0) {
		return _init("mmul", _mmul, 2);
	} else if (strncmp(functionName, "mdiv", FUNCTIONNAMELENGTH) == 0) {
		return _init("mdiv", _mdiv, 2);
	} else if (strncmp(functionName, "mabs", FUNCTIONNAMELENGTH) == 0) {
		return _init("mabs", _mabs, 1);
	} else if (strncmp(functionName, "msqrt", FUNCTIONNAMELENGTH) == 0) {
		return _init("msqrt", _msqrt, 1);
	} else if (strncmp(functionName, "mpow", FUNCTIONNAMELENGTH) == 0) {
		return _init("mpow", _mpow, 2);
	} else if (strncmp(functionName, "mpowint", FUNCTIONNAMELENGTH) == 0) {
		return _init("mpowint", _mpowint, 2);
	} else if (strncmp(functionName, "msin", FUNCTIONNAMELENGTH) == 0) {
		return _init("msin", _msin, 1);
	} else if (strncmp(functionName, "mcos", FUNCTIONNAMELENGTH) == 0) {
		return _init("mcos", _mcos, 1);
	} else if (strncmp(functionName, "mtanh", FUNCTIONNAMELENGTH) == 0) {
		return _init("mtanh", _mtanh, 1);
	} else if (strncmp(functionName, "mtan", FUNCTIONNAMELENGTH) == 0) {
		return _init("mtan", _mtan, 1);
	} else if (strncmp(functionName, "mexp", FUNCTIONNAMELENGTH) == 0) {
		return _init("mexp", _mexp, 1);
	} else if (strncmp(functionName, "mGT", FUNCTIONNAMELENGTH) == 0) {
		return _init("mGT", _mGT, 2);
	} else if (strncmp(functionName, "mLT", FUNCTIONNAMELENGTH) == 0) {
		return _init("mLT", _mLT, 2);
	}

	//STATISTICAL

	else if (strncmp(functionName, "stedv", FUNCTIONNAMELENGTH) == 0) {
		return _init("stedv", _stdev, 1);
	} else if (strncmp(functionName, "skew", FUNCTIONNAMELENGTH) == 0) {
		return _init("skew", _skew, 1);
	} else if (strncmp(functionName, "kurtosis", FUNCTIONNAMELENGTH) == 0) {
		return _init("kurtosis", _kurtosis, 1);
	} else if (strncmp(functionName, "mean", FUNCTIONNAMELENGTH) == 0) {
		return _init("mean", _mean, 1);
	} else if (strncmp(functionName, "median", FUNCTIONNAMELENGTH) == 0) {
		return _init("median", _median, 1);
	}

	else {
		printf("Warning: function '%s' is not known and was not added.\n",
				functionName);
	}

	return NULL;
}

//-----------------------------------------------------------------
//                       MIXED FUNCTIONS
//-----------------------------------------------------------------

struct matrix *_head(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {

	struct matrix *m = matrices[0];

	return _initialiseMatrixFromScalar(m->data[0][0]);
}

struct matrix *_last(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {

	struct matrix *m = matrices[0];

	if (m->cols == 1) {
		return _copyMatrixOf(m);
	}

	return _initialiseMatrixFromScalar(m->data[0][m->cols - 1]);
}

struct matrix *_length(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	struct matrix *m = matrices[0];

	return _initialiseMatrixFromScalar(m->cols);
}

struct matrix *_tail(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	struct matrix *m = matrices[0];

	if (m->cols == 1) {
		return _initialiseMatrixFromScalar(0);
	}

	return _initialiseMatrixFromArray(1, m->cols - 1, &(m->data[0][1]));
}

struct matrix *_diff(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	struct matrix *m = matrices[0];

	if (m->cols == 1) {
		return _mulWithScalar(_copyMatrixOf(m), -1);
	}

	struct matrix *m_ = _copyMatrixOf(m);

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m_->data[i][j] = m->data[i][j] - m->data[i][(j + 1) % m->cols];
		}
	}

	return m_;
}

struct matrix *_avgdiff(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	struct matrix *m = matrices[0];

	if (m->cols == 1) {
		return _copyMatrixOf(m);
	}

	struct matrix *m_ = _copyMatrixOf(m);

	for (int i = 0; i < m->rows; i++) {
		double sum = 0;
		for (int j = 0; j < m->cols; j++) {
			sum += m->data[i][j];
		}
		m_->data[i][0] = (double) sum / m->cols;
	}

	return m_;
}

struct matrix *_rotate(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	struct matrix *m = matrices[0];

	if (m->cols == 1) {
		return _copyMatrixOf(m);
	}

	struct matrix *m_ = _copyMatrixOf(m);

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m_->data[i][j] = m->data[i][(j + 1) % m->cols];
		}
	}

	return m_;
}

struct matrix *_reverse(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	struct matrix *m = matrices[0];

	if (m->cols == 1) {
		return _copyMatrixOf(m);
	}

	struct matrix *m_ = _copyMatrixOf(m);

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m_->data[i][j] = m->data[i][m->cols - 1 - j];
		}
	}

	return m_;
}

struct matrix *_pushback(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	struct matrix *_m = _initialiseMatrix(1,
			matrices[0]->cols + matrices[1]->cols);
	int i = 0;
	for (; i < matrices[0]->cols; i++) {
		_m->data[0][i] = matrices[0]->data[0][i];
	}

	for (int j = 0; j < matrices[1]->cols; j++, i++) {
		_m->data[0][i] = matrices[1]->data[0][j];
	}

	return _m;
}

struct matrix *_pushfront(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	struct matrix *_m = _initialiseMatrix(1,
			matrices[0]->cols + matrices[1]->cols);
	int i = 0;
	for (; i < matrices[1]->cols; i++) {
		_m->data[0][i] = matrices[1]->data[0][i];
	}

	for (int j = 0; j < matrices[0]->cols; j++, i++) {
		_m->data[0][i] = matrices[0]->data[0][j];
	}

	return _m;
}

struct matrix *_set(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	int index = -1;
	if (matrices[0]->rows == 1 && matrices[0]->cols == 1) {
		index = 0;
	} else if (matrices[1]->rows == 1 && matrices[1]->cols == 1) {
		index = 1;
	}

	//no scalar values
	if (-1 == index) {
		//return random matrix
		return matrices[rand() % 2];
	}

	//if other scalar too
	if (matrices[1 - index]->rows == 1 && matrices[1 - index]->cols == 1) {
		return _pushback(numInputs, matrices, connectionWeights);
	}

	struct matrix *_m = _initialiseMatrix(matrices[1 - index]->rows,
			matrices[1 - index]->cols);
	for (int i = 0; i < _m->cols; i++) {
		_m->data[0][i] = matrices[index]->data[0][0];
	}

	return _m;
}

struct matrix *_sum(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _sumElements(matrices[0], connectionWeights);
}

struct matrix *_madd(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _add(matrices[0], matrices[1], connectionWeights);
}

struct matrix *_msub(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _sub(matrices[0], matrices[1], connectionWeights);
}

struct matrix *_mmul(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _mul(matrices[0], matrices[1], connectionWeights);
}

struct matrix *_mdiv(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _div(matrices[0], matrices[1], connectionWeights);
}

struct matrix *_mabs(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _abs(matrices[0], connectionWeights);
}

struct matrix *_msqrt(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _sqrt(matrices[0], connectionWeights);
}

struct matrix *_mpow(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _pow(matrices[0], matrices[1], connectionWeights);
}

struct matrix *_mpowint(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _powInt(matrices[0], matrices[1], connectionWeights);
}

struct matrix *_msin(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _sin(matrices[0], connectionWeights);
}

struct matrix *_mtan(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _tan(matrices[0], connectionWeights);
}

struct matrix *_mcos(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _cos(matrices[0], connectionWeights);
}

struct matrix *_mtanh(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _tanh(matrices[0], connectionWeights);
}

struct matrix *_mexp(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _exp(matrices[0], connectionWeights);
}

struct matrix *_mGT(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _gt(matrices[0], matrices[1], connectionWeights);
}

struct matrix *_mLT(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _lt(matrices[0], matrices[1], connectionWeights);
}

struct matrix *_stdev(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _standard_deviation(matrices[0], connectionWeights);
}

struct matrix *_skew(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_kurtosis(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mean(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return _arithmetic_mean(matrices[0], connectionWeights);
}

struct matrix *_median(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

