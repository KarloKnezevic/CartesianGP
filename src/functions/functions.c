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


double __sumInputs(const int numInputs, const double *inputs);

//-----------------------------------------------------------------
//                           FACTORY
//-----------------------------------------------------------------

struct function *_init(const char *functionName,
		double (*function)(const int numInputs, const double *inputs), int args) {
	struct function *object = (struct function*) malloc(
			sizeof(struct function));

	object->function = function;
	object->args = args;
	strncpy(object->functionName, functionName, FUNCTIONNAMELENGTH);

	return object;
}

struct function *getFunction(char const *functionName) {
	if (strncmp(functionName, "add", FUNCTIONNAMELENGTH) == 0) {
		return _init("add", _add, -1);
	} else if (strncmp(functionName, "sub", FUNCTIONNAMELENGTH) == 0) {
		return _init("sub", _sub, -1);
	} else if (strncmp(functionName, "mul", FUNCTIONNAMELENGTH) == 0) {
		return _init("mul", _mul, -1);
	} else if (strncmp(functionName, "div", FUNCTIONNAMELENGTH) == 0) {
		return _init("div", _divide, -1);
	} else if (strncmp(functionName, "abs", FUNCTIONNAMELENGTH) == 0) {
		return _init("abs", _absolute, 1);
	} else if (strncmp(functionName, "sqrt", FUNCTIONNAMELENGTH) == 0) {
		return _init("sqrt", _squareRoot, 1);
	} else if (strncmp(functionName, "sq", FUNCTIONNAMELENGTH) == 0) {
		return _init("sq", _square, 1);
	} else if (strncmp(functionName, "cube", FUNCTIONNAMELENGTH) == 0) {
		return _init("cube", _cube, 1);
	} else if (strncmp(functionName, "pow", FUNCTIONNAMELENGTH) == 0) {
		return _init("pow", _power, 2);
	} else if (strncmp(functionName, "exp", FUNCTIONNAMELENGTH) == 0) {
		return _init("exp", _exponential, 1);
	} else if (strncmp(functionName, "sin", FUNCTIONNAMELENGTH) == 0) {
		return _init("sin", _sine, 1);
	} else if (strncmp(functionName, "cos", FUNCTIONNAMELENGTH) == 0) {
		return _init("cos", _cosine, 1);
	} else if (strncmp(functionName, "tan", FUNCTIONNAMELENGTH) == 0) {
		return _init("tan", _tangent, 1);
	}

	// Boolean logic gates

	else if (strncmp(functionName, "and", FUNCTIONNAMELENGTH) == 0) {
		return _init("and", _and, -1);
	} else if (strncmp(functionName, "nand", FUNCTIONNAMELENGTH) == 0) {
		return _init("nand", _nand, -1);
	} else if (strncmp(functionName, "or", FUNCTIONNAMELENGTH) == 0) {
		return _init("or", _or, -1);
	} else if (strncmp(functionName, "nor", FUNCTIONNAMELENGTH) == 0) {
		return _init("nor", _nor, -1);
	} else if (strncmp(functionName, "xor", FUNCTIONNAMELENGTH) == 0) {
		return _init("xor", _xor, -1);
	} else if (strncmp(functionName, "xnor", FUNCTIONNAMELENGTH) == 0) {
		return _init("xnor", _xnor, -1);
	} else if (strncmp(functionName, "not", FUNCTIONNAMELENGTH) == 0) {
		return _init("not", _not, 1);
	}

	// Neuron functions

	else if (strncmp(functionName, "sig", FUNCTIONNAMELENGTH) == 0) {
		return _init("sig", _sigmoid, -1);
	} else if (strncmp(functionName, "gauss", FUNCTIONNAMELENGTH) == 0) {
		return _init("gauss", _gaussian, -1);
	} else if (strncmp(functionName, "step", FUNCTIONNAMELENGTH) == 0) {
		return _init("step", _step, -1);
	} else if (strncmp(functionName, "softsign", FUNCTIONNAMELENGTH) == 0) {
		return _init("soft", _softsign, -1);
	} else if (strncmp(functionName, "tanh", FUNCTIONNAMELENGTH) == 0) {
		return _init("tanh", _hyperbolicTangent, -1);
	}

	// other

	else if (strncmp(functionName, "rand", FUNCTIONNAMELENGTH) == 0) {
		return _init("rand", _randFloat, 0);
	} else if (strncmp(functionName, "1", FUNCTIONNAMELENGTH) == 0) {
		return _init("1", _constOne, 0);
	} else if (strncmp(functionName, "0", FUNCTIONNAMELENGTH) == 0) {
		return _init("0", _constZero, 0);
	} else if (strncmp(functionName, "pi", FUNCTIONNAMELENGTH) == 0) {
		return _init("pi", _constPI, 0);
	} else if (strncmp(functionName, "wire", FUNCTIONNAMELENGTH) == 0) {
		return _init("wire", _wire, 1);
	}

	else {
		printf("Warning: function '%s' is not known and was not added.\n",
				functionName);
	}

	return NULL;
}

//-----------------------------------------------------------------
//                          FUNCTIONS
//-----------------------------------------------------------------

double _add(const int numInputs, const double *inputs) {
	int i;
	double sum = inputs[0];

	for (i = 1; i < numInputs; i++) {
		sum += inputs[i];
	}

	return sum;
}

double _sub(const int numInputs, const double *inputs) {
	int i;
	double sum = inputs[0];

	for (i = 1; i < numInputs; i++) {
		sum -= inputs[i];
	}

	return sum;
}

double _mul(const int numInputs, const double *inputs) {
	int i;
	double multiplication = inputs[0];

	for (i = 1; i < numInputs; i++) {
		multiplication *= inputs[i];
	}

	return multiplication;
}

double _divide(const int numInputs, const double *inputs) {
	int i;
	double divide = inputs[0];

	for (i = 1; i < numInputs; i++) {
		divide /= inputs[i];
	}

	return divide;
}

//Node function abs. Returns the absolute of the first input
double _absolute(const int numInputs, const double *inputs) {
	return fabs(inputs[0]);
}

//Node function sqrt.  Returns the square root of the first input
double _squareRoot(const int numInputs, const double *inputs) {
	return sqrt(inputs[0]);
}

//Node function squ.  Returns the square of the first input
double _square(const int numInputs, const double *inputs) {
	return pow(inputs[0], 2);
}

//Node function cub.  Returns the cube of the first input
double _cube(const int numInputs, const double *inputs) {
	return pow(inputs[0], 3);
}

//Node function power.  Returns the first output to the power of the second
double _power(const int numInputs, const double *inputs) {
	return pow(inputs[0], inputs[1]);
}

//Node function exp.  Returns the exponential of the first input
double _exponential(const int numInputs, const double *inputs) {
	return exp(inputs[0]);
}

//Node function sin.  Returns the sine of the first input
double _sine(const int numInputs, const double *inputs) {
	return sin(inputs[0]);
}

//Node function cos.  Returns the cosine of the first input
double _cosine(const int numInputs, const double *inputs) {
	return cos(inputs[0]);
}

//Node function tan.  Returns the tangent of the first input
double _tangent(const int numInputs, const double *inputs) {
	return tan(inputs[0]);
}

//Node function one.  Always returns 1
double _constOne(const int numInputs, const double *inputs) {
	return 1;
}

//Node function zero.  Always returns 0
double _constZero(const int numInputs, const double *inputs) {
	return 0;
}

//Node function pi.  Always returns PI
double _constPI(const int numInputs, const double *inputs) {
	return M_PI;
}

//Node function rand.  Returns a random number between minus one and positive one
double _randFloat(const int numInputs, const double *inputs) {

	double random;

	random = (double) rand() / (double) RAND_MAX;

	random = (random * 2) - 1;

	return random;
}

/*
 Node function and. logical AND, returns '1' if all inputs are '1'
 else, '0'
 */
double _and(const int numInputs, const double *inputs) {
	int i;

	for (i = 0; i < numInputs; i++) {

		if (inputs[i] == 0) {
			return 0;
		}
	}

	return 1;
}

/*
 Node function nand. logical NAND, returns '0' if all inputs are '1'
 else, '1'
 */
double _nand(const int numInputs, const double *inputs) {
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
double _or(const int numInputs, const double *inputs) {
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
double _nor(const int numInputs, const double *inputs) {
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
double _xor(const int numInputs, const double *inputs) {
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
double _xnor(const int numInputs, const double *inputs) {
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

//Node function not. logical NOT, returns '1' if first input is '0', else '1'
double _not(const int numInputs, const double *inputs) {
	double out;

	if (inputs[0] == 0) {
		out = 1;
	} else {
		out = 0;
	}

	return out;
}

//Node function wire. simply acts as a wire returning the first input

double _wire(const int numInputs, const double *inputs) {
	double out;
	out = inputs[0];
	return out;
}

/*
 Node function sigmoid. returns the sigmoid of the sum of weighted inputs.
 The specific sigmoid function used in the logistic function.
 range: [0,1]
 */
double _sigmoid(const int numInputs, const double *inputs) {
	double inputSum;
	double out;

	inputSum = __sumInputs(numInputs, inputs);

	out = 1 / (1 + exp(-inputSum));

	return out;
}

/*
 Node function Gaussian. returns the Gaussian of the sum of weighted inputs.
 range: [0,1]
 */
double _gaussian(const int numInputs, const double *inputs) {
	double inputSum;
	double out;

	int centre = 0;
	int width = 1;

	inputSum = __sumInputs(numInputs, inputs);

	out = exp(-(pow(inputSum - centre, 2)) / (2 * pow(width, 2)));

	return out;
}

/*
 Node function step. returns the step function of the sum of weighted inputs.
 range: [0,1]
 */
double _step(const int numInputs, const double *inputs) {
	double inputSum;
	double out;

	inputSum = __sumInputs(numInputs, inputs);

	if (inputSum < 0) {
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
double _softsign(const int numInputs, const double *inputs) {
	double inputSum;
	double out;

	inputSum = __sumInputs(numInputs, inputs);

	out = inputSum / (1 + fabs(inputSum));

	return out;
}

/*
 Node function tanh. returns the tanh function of the sum of weighted inputs.
 range: [-1,1]
 */
double _hyperbolicTangent(const int numInputs, const double *inputs) {
	double inputSum;
	double out;

	inputSum = __sumInputs(numInputs, inputs);

	out = tanh(inputSum);

	return out;
}

/*
 Returns the sum of the inputs.
 */
double __sumInputs(const int numInputs, const double *inputs) {
	int i;
	double sum = 0;

	for (i = 0; i < numInputs; i++) {
		sum += inputs[i];
	}

	return sum;
}

