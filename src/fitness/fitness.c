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

double MatthewsCorrelationCoefficient(struct parameters *params,
		struct matrix *confusionMatrix) {
	return -1;
}

//-----------------------------------------------------------------
//                  Softmax function
//-----------------------------------------------------------------

/**
 * Returns values from 0 to K-1
 */
int softmax(struct parameters *params, struct chromosome *chromo) {
	return -1;
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
			if (abs(1.0 - _getDataSetSampleOutput(data, i, j)) <= EPSILON) {
				trueClass = j;
				break;
			}
		}

		if (trueClass == -1) {
			printf("ERROR: Dataset has non classified data. Terminating...\n");
			exit(0);
		}

		//add data to confusion matrix [TRUE CLASS][PREDICTED CLASS]
		confusionMatrix->data[trueClass][predictedClass] =
				confusionMatrix->data[trueClass][predictedClass] + 1;

	}

	/**
	 * Calculate Matthews correlation coefficient
	 */
	double MCC = MatthewsCorrelationCoefficient(params, confusionMatrix);

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
