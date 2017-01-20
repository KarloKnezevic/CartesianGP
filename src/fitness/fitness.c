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

		if (value > max) {
			max = SCALAR(_getChromosomeOutput(chromo, i));
			maxIndex = i;
		}
	}

	return maxIndex;
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

		_executeChromosome(chromo, _getDataSetSampleInputs(data, i));

		int predictedClass = softmax(params, chromo);

		int trueClass = -1;
		//if there is K classes, is is used binary notation, and right class is denoted by 1
		for (j = 0; j < params->numOutputs; j++) {
			if (fabs(1.0 - _getDataSetSampleOutput(data, i, j)) <= EPSILON) {
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

		//add data to confusion matrix [TRUE CLASS][PREDICTED CLASS]
		confusionMatrix->data[trueClass][predictedClass] =
				confusionMatrix->data[trueClass][predictedClass] + 1;

	}

//	MatthewsCorrelationCoefficient(confusionMatrix)
	double fitness = _computeAccuracy(confusionMatrix);

	//free resources
	_freeMatrix(confusionMatrix);

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
