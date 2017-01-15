/*
 * functionset.h
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef FUNCTIONSET_H_
#define FUNCTIONSET_H_

#include "constants/constants.h"
#include "math/lialg.h"

struct parameters;

struct functionSet {
	int numFunctions;

	char functionNames[FUNCTIONSETSIZE][FUNCTIONNAMELENGTH];

	int maxNumInputs[FUNCTIONSETSIZE];

	struct matrix *(*mFunctions[FUNCTIONSETSIZE])(const int numInputs,
			struct matrix **inputs, const double *connectionWeights, const double amplitude);
};

void _printFunctionSet(struct parameters *params);

void _copyFunctionSet(struct functionSet *funcSetDest,
		struct functionSet *funcSetSrc);

#endif /* FUNCTIONSET_H_ */
