/*
 * evaluator.h
 *
 *  Created on: 20. sij 2017.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef EVALUATOR_H_
#define EVALUATOR_H_

#include "../parameters.h"
#include "../math/lialg.h"
#include "../chromosome.h"
#include "../dataset.h"

struct evaluator {
	double accuracy;
	double error;
	double sensitivity;
	double specificity;
	double precision;
	double DOR;
	double F1;
};

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct evaluator *_initialiseEvaluator(struct parameters *params);

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
		struct dataSet *data, struct evaluator *eval);

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printEvaluator(struct evaluator *eval);

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeEvaluator(struct evaluator *eval);

//-----------------------------------------------------------------
//                             UTILITY
//-----------------------------------------------------------------

double _computeAccuracy(struct matrix *confusionMatrix);

double _computeError(struct matrix *confusionMatrix);

double _computeSensitivity(struct matrix *confusionMatrix);

double _computeSpecificity(struct matrix *confusionMatrix);

double _computePrecision(struct matrix *confusionMatrix);

double _computeDOR(struct matrix *confusionMatrix);

double _computeF1(struct matrix *confusionMatrix);

#endif /* EVALUATOR_H_ */
