/*
 * evaluator.c
 *
 *  Created on: 20. sij 2017.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "evaluator.h"

#include <stdlib.h>

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct evaluator *_initialiseEvaluator(struct parameters *params) {
	return NULL;
}

//-----------------------------------------------------------------
//                            GETTERS
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//                            SETTERS
//-----------------------------------------------------------------

//-----------------------------------------------------------------
//                            VALIDATE
//-----------------------------------------------------------------

void _validate(struct parameters *params, struct chromosome *chromo,
		struct dataSet *data, struct evaluator *eval) {

}

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printEvaluator(struct evaluator *eval) {

}

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeEvaluator(struct evaluator *eval) {

}

//-----------------------------------------------------------------
//                             UTILITY
//-----------------------------------------------------------------

double _computeAccuracy(struct matrix *confusionMatrix) {
	return 0.0;
}

double _computeError(struct matrix *confusionMatrix) {
	return 0.0;
}

double _computeSensitivity(struct matrix *confusionMatrix) {
	return 0.0;
}

double _computeSpecificity(struct matrix *confusionMatrix) {
	return 0.0;
}

double _computePrecision(struct matrix *confusionMatrix) {
	return 0.0;
}

double _computeDOR(struct matrix *confusionMatrix) {
	return 0.0;
}

double _computeF1(struct matrix *confusionMatrix) {
	return 0.0;
}
