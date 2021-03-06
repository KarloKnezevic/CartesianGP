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
			const double *connectionWeights, const double amplitude);

	int args;
	char functionName[FUNCTIONNAMELENGTH];
};

struct function *getFunction(char const *functionName);

char *getAllF();

//-----------------------------------------------------------------
//                       MIXED FUNCTIONS
//-----------------------------------------------------------------

struct matrix *_head(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_last(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_length(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_tail(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_diff(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_avgdiff(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_rotate(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_reverse(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_pushback(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_pushfront(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_set(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_sum(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_madd(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_msub(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mmul(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);
struct matrix *_mdiv(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mabs(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_msqrt(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mpow(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mpowint(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_msin(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mtan(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mcos(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mtanh(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mexp(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mGT(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mLT(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_stdev(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_skew(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_kurtosis(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_mean(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_median(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_max1(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_maxMisc(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_min1(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_minMisc(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_nop(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_const1(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);

struct matrix *_constVector1(const int numInputs, struct matrix **matrices,
		const double *connectionWeights, const double amplitude);


#endif /* FUNCTIONS_H_ */
