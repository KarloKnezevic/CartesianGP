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
		return _init("mabs", _mabs, 2);
	} else if (strncmp(functionName, "msqrt", FUNCTIONNAMELENGTH) == 0) {
		return _init("msqrt", _msqrt, 2);
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
	return NULL;
}

struct matrix *_pushfront(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_set(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_sum(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_madd(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_msub(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mmul(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mdiv(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mabs(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_msqrt(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mpow(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mpowint(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_msin(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mtan(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mcos(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mtanh(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mexp(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mGT(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_mLT(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

