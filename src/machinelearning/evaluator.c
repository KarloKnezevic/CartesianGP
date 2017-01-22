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

#define _EVAL_CLASSES_	4

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

	eval->F1_macro = 0.0;
	eval->F1_micro = 0.0;

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
	eval->F1_micro = _computeF1_micro(confusionMatrix);
	eval->F1_macro = _computeF1_macro(confusionMatrix);
}

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printEvaluator(struct parameters *params, struct evaluator *eval) {
	if (eval == NULL) {
		printf(
				"Error: evaluator has not been initialised and cannot be printed.\n");
		return;
	}

	LOG(params,
			"\n\n-----------------------------------------------------------\n");
	LOG(params, "                     *Evaluator*                           \n");
	LOG(params, "-----------------------------------------------------------\n");
	LOG(params, "Accuracy:\t\t%f\n", eval->accuracy);
	LOG(params, "Error:\t\t\t%f\n", eval->error);
	LOG(params, "Sensitivity(R):\t\t%f\n", eval->sensitivity);
	LOG(params, "Specificity:\t\t%f\n", eval->specificity);
	LOG(params, "Precision(P):\t\t%f\n", eval->precision);
	LOG(params, "DOR:\t\t\t%f\n", eval->DOR);
	LOG(params, "F1:\t\t\t%f\n\n", eval->F1);
	LOG(params, "F1 micro:\t\t%f\n", eval->F1_micro);
	LOG(params, "F1 macro:\t\t%f\n", eval->F1_macro);
	LOG(params,
			"-----------------------------------------------------------\n\n");
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

//void _TEST_EVAL() {
//	struct matrix *confusionMatrix = _initialiseMatrix(3, 3);
//	confusionMatrix->data[0][0] = 100;
//	confusionMatrix->data[0][1] = 10;
//	confusionMatrix->data[0][2] = 1;
//	confusionMatrix->data[1][0] = 2;
//	confusionMatrix->data[1][1] = 2;
//	confusionMatrix->data[1][2] = 3;
//	confusionMatrix->data[2][0] = 8;
//	confusionMatrix->data[2][1] = 5;
//	confusionMatrix->data[2][2] = 400;
//
//	struct evaluator *eval = _initialiseEvaluator(NULL);
//
//	_calculateAllMeasures(eval, confusionMatrix);
//	_printEvaluator(eval);
//
//	_freeEvaluator(eval);
//	_freeMatrix(confusionMatrix);
//}

struct matrix *_calculate_4_class(struct matrix *confusionMatrix, int class,
		struct matrix *res) {
	for (int true = 0; true < confusionMatrix->rows; true++) {
		for (int predicted = 0; predicted < confusionMatrix->cols;
				predicted++) {

			//TP
			if (true == predicted && true == class) {
				res->data[class][EVAL_TP] +=
						confusionMatrix->data[true][predicted];
			}

			//TN
			if (true != class && predicted != class) {
				res->data[class][EVAL_TN] +=
						confusionMatrix->data[true][predicted];
			}

			//FP
			if (true != class && predicted == class) {
				res->data[class][EVAL_FP] +=
						confusionMatrix->data[true][predicted];
			}

			//FN
			if (true == class && predicted != class) {
				res->data[class][EVAL_FN] +=
						confusionMatrix->data[true][predicted];
			}
		}
	}

	return res;
}

double _computeAccuracy(struct matrix *confusionMatrix) {
	if (NULL == confusionMatrix) {
		return 0.0;
	}

	struct matrix *measures = _initialiseMatrix(confusionMatrix->rows,
	_EVAL_CLASSES_);

	double acc = 0;
	int evals = 0;
	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);

		acc += (measures->data[class][EVAL_TP] + measures->data[class][EVAL_TN])
				/ (measures->data[class][EVAL_TP]
						+ measures->data[class][EVAL_TN]
						+ measures->data[class][EVAL_FP]
						+ measures->data[class][EVAL_FN]);

		evals++;

		if (2 == confusionMatrix->rows) {
			break;
		}
	}

	acc /= evals;

	_freeMatrix(measures);

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

	struct matrix *measures = _initialiseMatrix(confusionMatrix->rows,
	_EVAL_CLASSES_);

	double sensitivity = 0;
	int evals = 0;
	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);

		sensitivity += measures->data[class][EVAL_TP]
				/ (measures->data[class][EVAL_TP]
						+ measures->data[class][EVAL_FN]);

		evals++;
		if (2 == confusionMatrix->rows) {
			break;
		}
	}

	sensitivity /= evals;

	_freeMatrix(measures);

	return sensitivity;
}

double _computeSpecificity(struct matrix *confusionMatrix) {
	if (NULL == confusionMatrix) {
		return 0.0;
	}

	struct matrix *measures = _initialiseMatrix(confusionMatrix->rows,
	_EVAL_CLASSES_);

	double specificity = 0;
	int evals = 0;
	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);

		specificity += measures->data[class][EVAL_TN]
				/ (measures->data[class][EVAL_TN]
						+ measures->data[class][EVAL_FP]);

		evals++;
		if (2 == confusionMatrix->rows) {
			break;
		}
	}

	specificity /= evals;

	_freeMatrix(measures);

	return specificity;
}

double _computePrecision(struct matrix *confusionMatrix) {
	if (NULL == confusionMatrix) {
		return 0.0;
	}

	struct matrix *measures = _initialiseMatrix(confusionMatrix->rows,
	_EVAL_CLASSES_);

	double precision = 0;
	int evals = 0;
	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);

		precision += measures->data[class][EVAL_TP]
				/ (measures->data[class][EVAL_TP]
						+ measures->data[class][EVAL_FP]);

		evals++;
		if (2 == confusionMatrix->rows) {
			break;
		}
	}

	precision /= evals;

	_freeMatrix(measures);

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

//-----------------------------------------------------------------
//                  Matthews correlation coefficient
//-----------------------------------------------------------------

#define CC(__x__, __y__) (confusionMatrix->data[__x__][__y__])
double MatthewsCorrelationCoefficient(struct matrix *confusionMatrix) {
	int bound = confusionMatrix->cols;

	double numerator = 0.0;
	for (int k = 0; k < bound; k++) {
		for (int l = 0; l < bound; l++) {
			for (int m = 0; m < bound; m++) {

				numerator += (CC(k,k) * CC(l, m)) - (CC(k,l) * CC(m, k));

			}
		}
	}

	double denominator1 = 0.0;
	for (int k = 0; k < bound; k++) {
		double sum1 = 0.0;
		for (int l = 0; l < bound; l++) {
			sum1 += CC(k, l);
		}

		double sum2 = 0.0;
		for (int _k = 0; _k < bound; _k++) {
			if (_k != k) {
				for (int l = 0; l < bound; l++) {
					sum2 += CC(_k, l);
				}
			}
		}

		denominator1 += sum1 * sum2;
	}

	double denominator2 = 0.0;
	for (int k = 0; k < bound; k++) {
		double sum1 = 0.0;
		for (int l = 0; l < bound; l++) {
			sum1 += CC(l, k);
		}

		double sum2 = 0.0;
		for (int _k = 0; _k < bound; _k++) {
			if (_k != k) {
				for (int l = 0; l < bound; l++) {
					sum2 += CC(l, _k);
				}
			}
		}

		denominator2 += sum1 * sum2;
	}

	if (denominator1 < EPSILON || denominator2 < EPSILON) {
		//no better then random classification
		return 0;
	}

	double MCC = numerator / (sqrt(denominator1) * sqrt(denominator2));

	return MCC;
}

//-----------------------------------------------------------------
//                       F MEASURES
//-----------------------------------------------------------------

double _computeFn(struct matrix *confusionMatrix, int n) {
	double sensitivity = _computeSensitivity(confusionMatrix);
	double precision = _computePrecision(confusionMatrix);

	return ((1 + n * n) * sensitivity * precision)
			/ ((n * n) * precision + sensitivity);
}

double _computeF1(struct matrix *confusionMatrix) {
	return _computeFn(confusionMatrix, 1);
}

double _computeF1_micro(struct matrix *confusionMatrix) {
	struct matrix *measures = _initialiseMatrix(confusionMatrix->rows,
	_EVAL_CLASSES_);

	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);

		if (class > 0) {
			measures->data[0][EVAL_TP] += measures->data[class][EVAL_TP];
			measures->data[0][EVAL_FP] += measures->data[class][EVAL_FP];
			measures->data[0][EVAL_FN] += measures->data[class][EVAL_FN];
		}
	}

	double precision = measures->data[0][EVAL_TP]
			/ (measures->data[0][EVAL_TP] + measures->data[0][EVAL_FP]);

	double sensitivity = measures->data[0][EVAL_TP]
			/ (measures->data[0][EVAL_TP] + measures->data[0][EVAL_FN]);

	double F = (2 * precision * sensitivity) / (precision + sensitivity);

	_freeMatrix(measures);

	return F;
}

double _computeF1_macro(struct matrix *confusionMatrix) {

	struct matrix *measures = _initialiseMatrix(confusionMatrix->rows,
	_EVAL_CLASSES_);

	double F = 0.0;
	double precision, sensitivity;
	for (int class = 0; class < confusionMatrix->rows; class++) {
		measures = _calculate_4_class(confusionMatrix, class, measures);

		precision = measures->data[class][EVAL_TP]
				/ (measures->data[class][EVAL_TP]
						+ measures->data[class][EVAL_FP]);

		sensitivity = measures->data[class][EVAL_TP]
				/ (measures->data[class][EVAL_TP]
						+ measures->data[class][EVAL_FN]);

		F += (2 * precision * sensitivity) / (precision + sensitivity);
	}

	_freeMatrix(measures);

	return F / confusionMatrix->rows;
}
