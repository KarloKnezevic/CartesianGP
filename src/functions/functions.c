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

double sumWeigtedInputs(const int numInputs, const double *inputs,
		const double *connectionWeights);

//-----------------------------------------------------------------
//                           FACTORY
//-----------------------------------------------------------------

struct function *_initScalarToMatrix(const char *functionName,
		double (*function)(const int numInputs, const double *inputs,
				const double *connectionWeights), int args) {

	struct function *object = (struct function*) malloc(
			sizeof(struct function));

//	object->function = function;
	object->args = args;
	strncpy(object->functionName, functionName, FUNCTIONNAMELENGTH);

	return object;
}

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

struct function *getFunction(char const *functionName) {
	if (strncmp(functionName, "add", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("add", _add, -1);
	} else if (strncmp(functionName, "sub", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("sub", _sub, -1);
	} else if (strncmp(functionName, "mul", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("mul", _mul, -1);
	} else if (strncmp(functionName, "div", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("div", _divide, -1);
	} else if (strncmp(functionName, "abs", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("abs", _absolute, 1);
	} else if (strncmp(functionName, "sqrt", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("sqrt", _squareRoot, 1);
	} else if (strncmp(functionName, "sq", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("sq", _square, 1);
	} else if (strncmp(functionName, "cube", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("cube", _cube, 1);
	} else if (strncmp(functionName, "pow", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("pow", _power, 2);
	} else if (strncmp(functionName, "exp", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("exp", _exponential, 1);
	} else if (strncmp(functionName, "sin", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("sin", _sine, 1);
	} else if (strncmp(functionName, "cos", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("cos", _cosine, 1);
	} else if (strncmp(functionName, "tan", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("tan", _tangent, 1);
	}

	// Boolean logic gates

	else if (strncmp(functionName, "and", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("and", _and, -1);
	} else if (strncmp(functionName, "nand", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("nand", _nand, -1);
	} else if (strncmp(functionName, "or", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("or", _or, -1);
	} else if (strncmp(functionName, "nor", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("nor", _nor, -1);
	} else if (strncmp(functionName, "xor", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("xor", _xor, -1);
	} else if (strncmp(functionName, "xnor", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("xnor", _xnor, -1);
	} else if (strncmp(functionName, "not", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("not", _not, 1);
	}

	// Neuron functions

	else if (strncmp(functionName, "sig", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("sig", _sigmoid, -1);
	} else if (strncmp(functionName, "gauss", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("gauss", _gaussian, -1);
	} else if (strncmp(functionName, "step", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("step", _step, -1);
	} else if (strncmp(functionName, "softsign", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("soft", _softsign, -1);
	} else if (strncmp(functionName, "tanh", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("tanh", _hyperbolicTangent, -1);
	}

	// other

	else if (strncmp(functionName, "rand", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("rand", _randFloat, 0);
	} else if (strncmp(functionName, "1", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("1", _constOne, 0);
	} else if (strncmp(functionName, "0", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("0", _constZero, 0);
	} else if (strncmp(functionName, "pi", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("pi", _constPI, 0);
	} else if (strncmp(functionName, "wire", FUNCTIONNAMELENGTH) == 0) {
		return _initScalarToMatrix("wire", _wire, 1);
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
	return NULL;
}

struct matrix *_last(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_length(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_tail(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_diff(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_avgdiff(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_rotate(const int numInputs, struct matrix **matrices,
		const double *connectionWeights) {
	return NULL;
}

struct matrix *_reverse(const int numInputs, struct matrix **matrices,
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

//-----------------------------------------------------------------
//                          FUNCTIONS
//-----------------------------------------------------------------

double _add(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;
	double sum = inputs[0];

	for (i = 1; i < numInputs; i++) {
		sum += inputs[i];
	}

	return sum;
}

/*
 Node function sub. Returns the first input minus all remaining inputs.
 */
double _sub(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;
	double sum = inputs[0];

	for (i = 1; i < numInputs; i++) {
		sum -= inputs[i];
	}

	return sum;
}

/*
 Node function mul. Returns the multiplication of all the inputs.
 */
double _mul(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;
	double multiplication = inputs[0];

	for (i = 1; i < numInputs; i++) {
		multiplication *= inputs[i];
	}

	return multiplication;
}

/*
 Node function div. Returns the first input divided by the second input divided by the third input etc
 */
double _divide(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;
	double divide = inputs[0];

	for (i = 1; i < numInputs; i++) {
		divide /= inputs[i];
	}

	return divide;
}

/*
 Node function abs. Returns the absolute of the first input
 */
double _absolute(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	return fabs(inputs[0]);
}

/*
 Node function sqrt.  Returns the square root of the first input
 */
double _squareRoot(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	return sqrt(inputs[0]);
}

/*
 Node function squ.  Returns the square of the first input
 */
double _square(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	return pow(inputs[0], 2);
}

/*
 Node function cub.  Returns the cube of the first input
 */
double _cube(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	return pow(inputs[0], 3);
}

/*
 Node function power.  Returns the first output to the power of the second
 */
double _power(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	return pow(inputs[0], inputs[1]);
}

/*
 Node function exp.  Returns the exponential of the first input
 */
double _exponential(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	return exp(inputs[0]);
}

/*
 Node function sin.  Returns the sine of the first input
 */
double _sine(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	return sin(inputs[0]);
}

/*
 Node function cos.  Returns the cosine of the first input
 */
double _cosine(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	return cos(inputs[0]);
}

/*
 Node function tan.  Returns the tangent of the first input
 */
double _tangent(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	return tan(inputs[0]);
}

/*
 Node function one.  Always returns 1
 */
double _constOne(const int numInputs, const double *inputs,
		const double *connectionWeights) {
	return 1;
}

/*
 Node function one.  Always returns 0
 */
double _constZero(const int numInputs, const double *inputs,
		const double *connectionWeights) {
	return 0;
}

/*
 Node function one.  Always returns PI
 */
double _constPI(const int numInputs, const double *inputs,
		const double *connectionWeights) {
	return M_PI;
}

/*
 Node function rand.  Returns a random number between minus one and positive one
 */
double _randFloat(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	double random;

	random = (double) rand() / (double) RAND_MAX;

	random = (random * 2) - 1;

	return random;
}

/*
 Node function and. logical AND, returns '1' if all inputs are '1'
 else, '0'
 */
double _and(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;

	for (i = 0; i < numInputs; i++) {

		if (inputs[i] == 0) {
			return 0;
		}
	}

	return 1;
}

/*
 Node function and. logical NAND, returns '0' if all inputs are '1'
 else, '1'
 */
double _nand(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;

	for (i = 0; i < numInputs; i++) {

		if (inputs[i] == 0) {
			return 1;
		}
	}

	return 0;
}

/*
 Node function or. logical OR, returns '0' if all inputs are '0'
 else, '1'
 */
double _or(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;

	for (i = 0; i < numInputs; i++) {

		if (inputs[i] == 1) {
			return 1;
		}
	}

	return 0;
}

/*
 Node function nor. logical NOR, returns '1' if all inputs are '0'
 else, '0'
 */
double _nor(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;

	for (i = 0; i < numInputs; i++) {

		if (inputs[i] == 1) {
			return 0;
		}
	}

	return 1;
}

/*
 Node function xor. logical XOR, returns '1' iff one of the inputs is '1'
 else, '0'. AKA 'one hot'.
 */
double _xor(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;
	int numOnes = 0;
	int out;

	for (i = 0; i < numInputs; i++) {

		if (inputs[i] == 1) {
			numOnes++;
		}

		if (numOnes > 1) {
			break;
		}
	}

	if (numOnes == 1) {
		out = 1;
	} else {
		out = 0;
	}

	return out;
}

/*
 Node function xnor. logical XNOR, returns '0' iff one of the inputs is '1'
 else, '1'.
 */
double _xnor(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;
	int numOnes = 0;
	int out;

	for (i = 0; i < numInputs; i++) {

		if (inputs[i] == 1) {
			numOnes++;
		}

		if (numOnes > 1) {
			break;
		}
	}

	if (numOnes == 1) {
		out = 0;
	} else {
		out = 1;
	}

	return out;
}

/*
 Node function not. logical NOT, returns '1' if first input is '0', else '1'
 */
double _not(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	double out;

	if (inputs[0] == 0) {
		out = 1;
	} else {
		out = 0;
	}

	return out;
}

/*
 Node function wire. simply acts as a wire returning the first input
 */
double _wire(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	double out;

	out = inputs[0];

	return out;
}

/*
 Node function sigmoid. returns the sigmoid of the sum of weighted inputs.
 The specific sigmoid function used in the logistic function.
 range: [0,1]
 */
double _sigmoid(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	double weightedInputSum;
	double out;

	weightedInputSum = sumWeigtedInputs(numInputs, inputs, connectionWeights);

	out = 1 / (1 + exp(-weightedInputSum));

	return out;
}

/*
 Node function Gaussian. returns the Gaussian of the sum of weighted inputs.
 range: [0,1]
 */
double _gaussian(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	double weightedInputSum;
	double out;

	int centre = 0;
	int width = 1;

	weightedInputSum = sumWeigtedInputs(numInputs, inputs, connectionWeights);

	out = exp(-(pow(weightedInputSum - centre, 2)) / (2 * pow(width, 2)));

	return out;
}

/*
 Node function step. returns the step function of the sum of weighted inputs.
 range: [0,1]
 */
double _step(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	double weightedInputSum;
	double out;

	weightedInputSum = sumWeigtedInputs(numInputs, inputs, connectionWeights);

	if (weightedInputSum < 0) {
		out = 0;
	} else {
		out = 1;
	}

	return out;
}

/*
 Node function step. returns the step function of the sum of weighted inputs.
 range: [-1,1]
 */
double _softsign(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	double weightedInputSum;
	double out;

	weightedInputSum = sumWeigtedInputs(numInputs, inputs, connectionWeights);

	out = weightedInputSum / (1 + fabs(weightedInputSum));

	return out;
}

/*
 Node function tanh. returns the tanh function of the sum of weighted inputs.
 range: [-1,1]
 */
double _hyperbolicTangent(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	double weightedInputSum;
	double out;

	weightedInputSum = sumWeigtedInputs(numInputs, inputs, connectionWeights);

	out = tanh(weightedInputSum);

	return out;
}

/*
 Returns the sum of the weighted inputs.
 */
double sumWeigtedInputs(const int numInputs, const double *inputs,
		const double *connectionWeights) {

	int i;
	double weightedSum = 0;

	for (i = 0; i < numInputs; i++) {
		weightedSum += (inputs[i] * connectionWeights[i]);
	}

	return weightedSum;
}

