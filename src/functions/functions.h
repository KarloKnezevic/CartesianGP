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
