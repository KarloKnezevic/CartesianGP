/*
 * functions.h
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "../constants/constants.h"
#include "../math/lialg.h"

//-----------------------------------------------------------------
//                           FACTORY
//-----------------------------------------------------------------

struct function {
	struct matrix *(*mFunction)(const int numInputs, struct matrix **matrices,
			const double *connectionWeights);

	int args;
	char functionName[FUNCTIONNAMELENGTH];
};

struct function *getFunction(char const *functionName);

//-----------------------------------------------------------------
//                       MIXED FUNCTIONS
//-----------------------------------------------------------------

struct matrix *_head(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_last(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_length(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_tail(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_diff(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_avgdiff(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_rotate(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_reverse(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_pushfront(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_set(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_sum(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_madd(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_msub(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mmul(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);
struct matrix *_mdiv(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mabs(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_msqrt(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mpow(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mpowint(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_msin(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mtan(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mcos(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mtanh(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mexp(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mGT(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mLT(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

//-----------------------------------------------------------------
//                       SCALAR FUNCTIONS
//-----------------------------------------------------------------

double _add(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _sub(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _mul(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _divide(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _and(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _absolute(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _squareRoot(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _square(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _cube(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _power(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _exponential(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _sine(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _cosine(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _tangent(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _randFloat(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _constOne(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _constZero(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _constPI(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _nand(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _or(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _nor(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _xor(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _xnor(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _not(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _wire(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _sigmoid(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _gaussian(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _step(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _softsign(const int numInputs, const double *inputs,
		const double *connectionWeights);
double _hyperbolicTangent(const int numInputs, const double *inputs,
		const double *connectionWeights);

#endif /* FUNCTIONS_H_ */
