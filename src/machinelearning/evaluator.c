/*
 * evaluator.c
 *
 *  Created on: 20. sij 2017.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "evaluator.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define _tp measures[EVAL_TP]
#define _tn measures[EVAL_TN]
#define _fp measures[EVAL_FP]
#define _fn measures[EVAL_FN]

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct evaluator *_initialiseEvaluator(struct parameters *params) {
	struct evaluator *eval = (struct evaluator *) malloc(
			sizeof(struct evaluator));

	eval->accuracy = 0.0;
	eval->error = 0.0;
	eval->sensitivity = 0.0;
	eval->specificity = 0.0;
	eval->precision = 0.0;
	eval->DOR = 0.0;
	eval->F1 = 0.0;

	return eval;
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

void _calculateAllMeasures(struct evaluator *eval,
		struct matrix *confusionMatrix) {

	if (NULL == eval) {
		printf("ERROR: evaluator is not initialised. Cannot save results.\n");
		return;
	}

	if (NULL == confusionMatrix) {
		printf(
				"ERROR: confusion matrix not initialised. Cannot compute measures.\n");
		return;
	}

	eval->accuracy = _computeAccuracy(confusionMatrix);
	eval->error = _computeError(confusionMatrix);
	eval->sensitivity = _computeSensitivity(confusionMatrix);
	eval->specificity = _computeSpecificity(confusionMatrix);
	eval->precision = _computePrecision(confusionMatrix);
	eval->DOR = _computeDOR(confusionMatrix);
	eval->F1 = _computeF1(confusionMatrix);
}

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printEvaluator(struct evaluator *eval) {
	if (eval == NULL) {
		printf(
				"Error: evaluator has not been initialised and cannot be printed.\n");
		return;
	}

	printf("-----------------------------------------------------------\n");
	printf("                     *Evaluator*                           \n");
	printf("-----------------------------------------------------------\n");
	printf("Accuracy:\t\t%f\n", eval->accuracy);
	printf("Error:\t\t%f\n", eval->error);
	printf("Sensitivity:\t\t%f\n", eval->sensitivity);
	printf("Specificity:\t\t%f\n", eval->specificity);
	printf("Precision:\t\t%f\n", eval->precision);
	printf("DOR:\t\t%f\n", eval->DOR);
	printf("F1:\t\t%f\n", eval->F1);
	printf("-----------------------------------------------------------\n\n");
}

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeEvaluator(struct evaluator *eval) {
	free(eval);
}

//-----------------------------------------------------------------
//                             UTILITY
//-----------------------------------------------------------------

void TEST_EVAL() {
	struct matrix *confusionMatrix = _initialiseMatrix(2, 2);
	confusionMatrix->data[0][0] = 6;
	confusionMatrix->data[0][1] = 2;
	confusionMatrix->data[1][0] = 12;
	confusionMatrix->data[1][1] = 130;

	struct evaluator *eval = _initialiseEvaluator(NULL);

	_calculateAllMeasures(confusionMatrix, eval);
	_printEvaluator(eval);

	_freeEvaluator(eval);
	_freeMatrix(confusionMatrix);
}

int *_calculate_4_class(struct matrix *confusionMatrix, int class, int *res) {
	if (NULL == res) {
		res = (int *) calloc(4, sizeof(int));
	}

	for (int true = 0; true < confusionMatrix->rows; true++) {
		for (int predicted = 0; predicted < confusionMatrix->cols;
				predicted++) {

			//TP
			if (true == predicted) {
				res[EVAL_TP] += confusionMatrix->data[true][predicted];
			}

			//TN
			if (true != class && predicted != class) {
				res[EVAL_TN] += confusionMatrix->data[true][predicted];
			}

			//FP
			if (true != class && predicted == class) {
				res[EVAL_FP] += confusionMatrix->data[true][predicted];
			}

			//FN
			if (true == class && predicted != class) {
				res[EVAL_FN] += confusionMatrix->data[true][predicted];
			}
		}
	}

	return res;
}

double _computeAccuracy(struct matrix *confusionMatrix) {
	if (NULL == confusionMatrix) {
		return 0.0;
	}

	int *measures = NULL;
	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);
	}

	double acc = (_tp+ _tn) / (confusionMatrix->cols * (_tp + _tn + _fp + _fn));

	free(measures);

	return acc;
}

double _computeError(struct matrix *confusionMatrix) {
	return 1.0 - _computeAccuracy(confusionMatrix);
}

double _computeSensitivity(struct matrix *confusionMatrix) {
	if (NULL == confusionMatrix) {
		return 0.0;
	}

	int *measures = NULL;
	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);
	}

	double sensitivity = (_tp) / (confusionMatrix->cols * (_tp + _fn));

	free(measures);

	return sensitivity;
}

double _computeSpecificity(struct matrix *confusionMatrix) {
	if (NULL == confusionMatrix) {
		return 0.0;
	}

	int *measures = NULL;
	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);
	}

	double specificity = (_tn) / (confusionMatrix->cols * (_tn + _fp));

	free(measures);

	return specificity;
}

double _computePrecision(struct matrix *confusionMatrix) {
	if (NULL == confusionMatrix) {
		return 0.0;
	}

	int *measures = NULL;
	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);
	}

	double precision = (_tp) / (confusionMatrix->cols * (_tp + _fp));

	free(measures);

	return precision;
}

double _computeDOR(struct matrix *confusionMatrix) {
	double sensitivity = _computeSensitivity(confusionMatrix);
	double specificity = _computeSpecificity(confusionMatrix);

	if (fabs(1 - sensitivity) < EPSILON || fabs(1 - specificity) < EPSILON) {
		return -1;
	}

	return (sensitivity * specificity) / ((1 - sensitivity) * (1 - specificity));
}

double _computeF1(struct matrix *confusionMatrix) {
	double sensitivity = _computeSensitivity(confusionMatrix);
	double specificity = _computeSpecificity(confusionMatrix);
	double precision = _computePrecision(confusionMatrix);

	return (2 * sensitivity * specificity) / (precision + sensitivity);
}
