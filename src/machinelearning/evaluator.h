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

#define EVAL_TP 	0
#define EVAL_TN 	1
#define EVAL_FP 	2
#define EVAL_FN 	3

struct evaluator {
	double accuracy;
	double error;
	double sensitivity;
	double specificity;
	double precision;
	double DOR;
	double F1;

	double F1_macro;
	double F1_micro;
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

void _calculateAllMeasures(struct evaluator *eval,
		struct matrix *confusionMatrix);

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printEvaluator(struct parameters *params, struct evaluator *eval);

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeEvaluator(struct evaluator *eval);

//-----------------------------------------------------------------
//                             UTILITY
//-----------------------------------------------------------------

/**
 * THE HIGHER, THE BETTER
 */
double _computeAccuracy(struct matrix *confusionMatrix);

/**
 * THE LOWER, THE BETTER
 */
double _computeError(struct matrix *confusionMatrix);

/**
 * THE HIGHER, THE BETTER
 *
 * This measure is appropriate if it's important to predict TRUE values.
 */
double _computeSensitivity(struct matrix *confusionMatrix);

/**
 * THE HIGHER, THE BETTER
 *
 * This measure is appropriate if it's important to predict NEGATIVE values.
 */
double _computeSpecificity(struct matrix *confusionMatrix);

/**
 * THE HIGHER, THE BETTER
 *
 * This measure calculates the probability that predicted value is true.
 */
double _computePrecision(struct matrix *confusionMatrix);

/**
 * THE HIGHER, THE BETTER
 *
 * The diagnostic odds ratio ranges from zero to infinity,
 * although for useful tests it is greater than one, and higher
 * diagnostic odds ratios are indicative of better test performance.
 * Diagnostic odds ratios less than one indicate that the test can be
 * improved by simply inverting the outcome of the test – the test is in
 * the wrong direction, while a diagnostic odds ratio of exactly one
 * means that the test is equally likely to predict a positive outcome
 * whatever the true condition – the test gives no information.
 */
double _computeDOR(struct matrix *confusionMatrix);

//-----------------------------------------------------------------
//                  Matthews correlation coefficient
//-----------------------------------------------------------------

double MatthewsCorrelationCoefficient(struct matrix *confusionMatrix);

//-----------------------------------------------------------------
//                       F MEASURES
//-----------------------------------------------------------------

double _computeFn(struct matrix *confusionMatrix, int n);

double _computeF1(struct matrix *confusionMatrix);

double _computeF1_micro(struct matrix *confusionMatrix);

double _computeF1_macro(struct matrix *confusionMatrix);

#endif /* EVALUATOR_H_ */
