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

double supervisedLearning(struct parameters *params, struct chromosome *chromo,
		struct dataSet *data) {
	int i, j;
	double error = 0;

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

	//for each data
	for (i = 0; i < _getNumDataSetSamples(data); i++) {

		_executeChromosome(chromo, _getDataSetSampleInputs(data, i));

		//for each output
		//TODO:think about error!
		for (j = 0; j < _getNumChromosomeOutputs(chromo); j++) {
			error += fabs(
					_getMatrixAsScalar(_getChromosomeOutput(chromo, j))
							- _getDataSetSampleOutput(data, i, j));
		}

	}

	return error;
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
