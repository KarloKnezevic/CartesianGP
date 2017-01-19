/*
 * fitness.c
 *
 *  Created on: 15. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "fitness.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../math/lialg.h"

#define SCALAR(X) _getMatrixAsScalar(X)

//-----------------------------------------------------------------
//                          ERROR
//-----------------------------------------------------------------

void validate(struct chromosome *chromo, struct dataSet *data) {
	if (_getNumChromosomeInputs(chromo) != _getNumDataSetInputs(data)) {
		printf(
				"Error: the number of chromosome inputs must match the number of inputs specified in the dataSet.\n");
		printf("Terminating.\n");
		exit(0);
	}

	if (_getNumChromosomeOutputs(chromo) != _getNumDataSetOutputs(data)) {
		printf(
				"Error: the number of chromosome outputs must match the number of outputs specified in the dataSet.\n");
		printf("Terminating.\n");
		exit(0);
	}
}

//-----------------------------------------------------------------
//                  Matthews correlation coefficient
//-----------------------------------------------------------------

#define CC(__x__, __y__) (confusionMatrix->data[__x__][__y__])

double MatthewsCorrelationCoefficient(struct parameters *params,
		struct matrix *confusionMatrix) {

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
//                  Softmax function
//-----------------------------------------------------------------

/**
 * Returns values from 0 to K-1
 *
 * In case of error, -1 returned
 */
int softmax(struct parameters *params, struct chromosome *chromo) {
	//return index of max output value

	//error state
	if (chromo->numOutputs < 1) {
		return -1;
	}

	int maxIndex = 0;
	double max = SCALAR(_getChromosomeOutput(chromo, maxIndex));

	for (int i = 0; i < _getNumChromosomeOutputs(chromo); i++) {
		double value = SCALAR(_getChromosomeOutput(chromo, i));

		if (params->print == 1) {
			printf("%.5f ", value);
		}

		if (value > max) {
			max = SCALAR(_getChromosomeOutput(chromo, i));
			maxIndex = i;
		}
	}

	if (params->print == 1) {
		printf("\n");
	}

	return maxIndex;
}

//-----------------------------------------------------------------
//                  Accuracy
//-----------------------------------------------------------------

int trueClassification(struct parameters *params,
		struct matrix *confusionMatrix) {

	int true = 0;
	for (int i = 0; i < confusionMatrix->cols; i++) {
		true += confusionMatrix->data[i][i];
	}

	return true;
}

//-----------------------------------------------------------------
//                  Supervised learning
//-----------------------------------------------------------------

double supervisedLearning(struct parameters *params, struct chromosome *chromo,
		struct dataSet *data) {
	int i, j;

	validate(chromo, data);

	/**
	 * Create confusion matrix.
	 * Confusion matrix has dimension K x K, where K is number of classes.
	 */
	struct matrix *confusionMatrix = _initialiseMatrix(params->numOutputs,
			params->numOutputs);

	//for each data
	for (i = 0; i < _getNumDataSetSamples(data); i++) {

		if (chromo->print == 1) {
			printf("Izvodim mrezu za\n");
			for (int k = 0; k < data->numInputs; k++) {
				printf("%d_", k);
				_printMatrix(data->inputData[i][k]);
				printf(" ");
			}
			printf("\n");

		}

		_executeChromosome(chromo, _getDataSetSampleInputs(data, i));

		int predictedClass = softmax(params, chromo);

		int trueClass = -1;
		//if there is K classes, is is used binary notation, and right class is denoted by 1
		for (j = 0; j < params->numOutputs; j++) {
			if (abs(1.0 - _getDataSetSampleOutput(data, i, j)) <= EPSILON) {
				trueClass = j;
				break;
			}
		}

		if (trueClass == -1 || predictedClass == -1) {
			printf("ERROR: Dataset has non classified data. "
					"Predicted: %d True: %d Data index: %d Terminating...\n",
					predictedClass, trueClass, i);
			exit(0);
		}

		if (chromo->print == 1) {
			printf("TRUE: %d PREDICTED: %d\n", trueClass, predictedClass);
		}


		//add data to confusion matrix [TRUE CLASS][PREDICTED CLASS]
		confusionMatrix->data[trueClass][predictedClass] =
				confusionMatrix->data[trueClass][predictedClass] + 1;

	}

	/**
	 * Calculate Matthews correlation coefficient
	 */
	//double MCC = MatthewsCorrelationCoefficient(params, confusionMatrix);
	double MCC = (double) trueClassification(params, confusionMatrix)
			/ (double) _getNumDataSetSamples(data);

	if (params->print == 1) {
		_printMatrix(confusionMatrix);
		printf("\n");
	}

	//free resources
	_freeMatrix(confusionMatrix);

	/**
	 * Return fitness as 1 - ABS( MCC )
	 */
	return 1 - fabs(MCC);
}

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setCustomFitnessFunction(struct parameters *params,
		double (*fitnessFunction)(struct parameters *params,
				struct chromosome *chromo, struct dataSet *data),
		char const *fitnessFunctionName) {

	if (fitnessFunction == NULL) {
		params->fitnessFunction = supervisedLearning;
		strncpy(params->fitnessFunctionName, "supervisedLearning",
		FITNESSFUNCTIONNAMELENGTH);
	} else {
		params->fitnessFunction = fitnessFunction;
		strncpy(params->fitnessFunctionName, fitnessFunctionName,
		FITNESSFUNCTIONNAMELENGTH);
	}
}
