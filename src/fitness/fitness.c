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
#include "../machinelearning/evaluator.h"
#include "../util.h"

#define SCALAR(_X_) 	_getMatrixAsScalar(_X_)
#define SIGMA_F(_Y_)	1.0 / (1 + exp(-SCALAR(_Y_)))

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
//                  Softmax function
//-----------------------------------------------------------------

/**
 * Returns values from 0 to K-1
 *
 * In case of error, -1 returned
 */
int softmax(struct parameters *params, struct chromosome *chromo,
		struct evaluator *eval, double *sqError, int trueClass) {
	//return index of max output value

	//error state
	if (chromo->numOutputs < 1) {
		return -1;
	}

	int maxIndex = 0;
	double max = SIGMA_F(_getChromosomeOutput(chromo, maxIndex));
	double outputForTrue = 0;

	for (int i = 0; i < _getNumChromosomeOutputs(chromo); i++) {
		double value = SIGMA_F(_getChromosomeOutput(chromo, i));

		if (i == trueClass) {
			outputForTrue = value;
		}

		if (NULL != eval) {
			LOG(params, "%f ", value);
		}

		if (value > max) {
			max = value;
			maxIndex = i;
		} else if (fabs(value - max) < EPSILON) {
			//if values same, randomly choose index
			maxIndex = _randInt(2) == 0 ? maxIndex : i;
		}
	}

	if (maxIndex != trueClass) {
		//square error
		*sqError += (max / outputForTrue) * (max / outputForTrue);
	}

	return maxIndex;
}

//-----------------------------------------------------------------
//                  Supervised learning
//-----------------------------------------------------------------

double supervisedLearning(struct parameters *params, struct chromosome *chromo,
		struct dataSet *data, struct evaluator *eval) {
	int i, j;

	validate(chromo, data);

	/**
	 * Create confusion matrix.
	 * Confusion matrix has dimension K x K, where K is number of classes.
	 */
	struct matrix *confusionMatrix = _initialiseMatrix(params->numOutputs,
			params->numOutputs);

	double sqError = 0;

	//for each data
	for (i = 0; i < _getNumDataSetSamples(data); i++) {

		_executeChromosome(chromo, _getDataSetSampleInputs(data, i));

		int trueClass = -1;
		//if there is K classes, is is used binary notation, and right class is denoted by 1
		for (j = 0; j < params->numOutputs; j++) {
			if (fabs(1.0 - _getDataSetSampleOutput(data, i, j)) <= EPSILON) {
				trueClass = j;
				break;
			}
		}

		int predictedClass = softmax(params, chromo, eval, &sqError, trueClass);

		if (trueClass == -1 || predictedClass == -1) {
			LOG(params, "ERROR: Dataset has non classified data. "
					"Predicted: %d True: %d Data index: %d Terminating...\n",
					predictedClass, trueClass, i);
			exit(0);
		}

		if (NULL != eval) {
			LOG(params, " | %d %d\n", trueClass, predictedClass);
		}

		//add data to confusion matrix [TRUE CLASS][PREDICTED CLASS]
		confusionMatrix->data[trueClass][predictedClass]++;

	}

//	MatthewsCorrelationCoefficient(confusionMatrix)
	double fitness = sqError;
	chromo->accuracy = _computeAccuracy(confusionMatrix);

	//eval
	if (NULL != eval) {
		_calculateAllMeasures(eval, confusionMatrix);
		printf("\n===Confusion matrix===\n");
		_printMatrix(confusionMatrix);
		printf("\n");
	}

	//free resources
	_freeMatrix(confusionMatrix);

	//if regularization enabled
	if (1 == params->L1regularization) {
		return fitness + chromo->regularization;
	}

	/**
	 * Return fitness as 1 - ABS( fitness )
	 */
	return 1 - fabs(fitness);
}

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setCustomFitnessFunction(struct parameters *params,
		double (*fitnessFunction)(struct parameters *params,
				struct chromosome *chromo, struct dataSet *data,
				struct evaluator *eval), char const *fitnessFunctionName) {

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
