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

struct matrix *_pushback(const int numInputs, struct matrix **matrices,
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

struct matrix *_stdev(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_skew(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_kurtosis(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_mean(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);

struct matrix *_median(const int numInputs, struct matrix **matrices,
		const double *connectionWeights);


#endif /* FUNCTIONS_H_ */
