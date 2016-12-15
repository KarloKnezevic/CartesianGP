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

//-----------------------------------------------------------------
//                           FACTORY
//-----------------------------------------------------------------

struct function {
	double (*function)(const int numInputs, const double *inputs);
	int args;
	char functionName[FUNCTIONNAMELENGTH];
};

struct function *getFunction(char const *functionName);

//-----------------------------------------------------------------
//                          FUNCTIONS
//-----------------------------------------------------------------

double _add(const int numInputs, const double *inputs);
double _sub(const int numInputs, const double *inputs);
double _mul(const int numInputs, const double *inputs);
double _divide(const int numInputs, const double *inputs);
double _and(const int numInputs, const double *inputs);
double _absolute(const int numInputs, const double *inputs);
double _squareRoot(const int numInputs, const double *inputs);
double _square(const int numInputs, const double *inputs);
double _cube(const int numInputs, const double *inputs);
double _power(const int numInputs, const double *inputs);
double _exponential(const int numInputs, const double *inputs);
double _sine(const int numInputs, const double *inputs);
double _cosine(const int numInputs, const double *inputs);
double _tangent(const int numInputs, const double *inputs);
double _randFloat(const int numInputs, const double *inputs);
double _constOne(const int numInputs, const double *inputs);
double _constZero(const int numInputs, const double *inputs);
double _constPI(const int numInputs, const double *inputs);
double _nand(const int numInputs, const double *inputs);
double _or(const int numInputs, const double *inputs);
double _nor(const int numInputs, const double *inputs);
double _xor(const int numInputs, const double *inputs);
double _xnor(const int numInputs, const double *inputs);
double _not(const int numInputs, const double *inputs);
double _wire(const int numInputs, const double *inputs);
double _sigmoid(const int numInputs, const double *inputs);
double _gaussian(const int numInputs, const double *inputs);
double _step(const int numInputs, const double *inputs);
double _softsign(const int numInputs, const double *inputs);
double _hyperbolicTangent(const int numInputs, const double *inputs);

#endif /* FUNCTIONS_H_ */
