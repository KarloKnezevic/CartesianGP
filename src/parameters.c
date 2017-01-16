/*
 * parameters.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions/functions.h"
#include "mutation/mutation.h"
#include "fitness/fitness.h"
#include "selection/selection.h"
#include "reproduction/reproduction.h"
#include "stream/stream.h"

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------
struct parameters *_initialiseParameters(const int numInputs,
		const int numNodes, const int numOutputs, const int arity) {

	struct parameters *params;

	params = (struct parameters*) malloc(sizeof(struct parameters));

	//DEFAULT PARAMETERS
	params->mu = MU;
	params->lambda = LAMBDA;
	params->evolutionaryStrategy = EVOLUTIONARYSTRATEGY;
	params->mutationRate = MUTATIONRATE;
	params->recurrentConnectionProbability = RECCURENTCONNECTIONPROBABILITY;
	params->connectionWeightRange = CONNECTIONWEIGHTRANGE;
	params->amplitudeRange = AMPLITUDERANGE;
	params->shortcutConnections = SHORTCUTCONNECTIONS;
	params->targetFitness = TARGETFITNESS;
	params->updateFrequency = UPDATEFREQUENCY;

	_setNumInputs(params, numInputs);
	_setNumNodes(params, numNodes);
	_setNumOutputs(params, numOutputs);
	_setArity(params, arity);

	params->mutationType = probabilisticMutation;
	strncpy(params->mutationTypeName, "probabilistic", MUTATIONTYPENAMELENGTH);

	params->funcSet = (struct functionSet*) malloc(sizeof(struct functionSet));
	params->funcSet->numFunctions = 0;

	params->fitnessFunction = supervisedLearning;
	strncpy(params->fitnessFunctionName, "supervisedLearning",
	FITNESSFUNCTIONNAMELENGTH);

	params->selectionScheme = selectFittest;
	strncpy(params->selectionSchemeName, "selectFittest",
	SELECTIONSCHEMENAMELENGTH);

	params->reproductionScheme = mutateRandomParent;
	strncpy(params->reproductionSchemeName, "mutateRandomParent",
	REPRODUCTIONSCHEMENAMELENGTH);

	srand(time(NULL));

	return params;
}

struct parameters *_initialiseParametersFromFile(char const *fileName,
		struct dataSet *trainingData, struct dataSet *testingData) {

	struct parameters *params;

	params = (struct parameters*) malloc(sizeof(struct parameters));

	//DEFAULT PARAMETERS
	params->mu = MU;
	params->lambda = LAMBDA;
	params->evolutionaryStrategy = EVOLUTIONARYSTRATEGY;
	params->mutationRate = MUTATIONRATE;
	params->recurrentConnectionProbability = RECCURENTCONNECTIONPROBABILITY;
	params->connectionWeightRange = CONNECTIONWEIGHTRANGE;
	params->amplitudeRange = AMPLITUDERANGE;
	params->shortcutConnections = SHORTCUTCONNECTIONS;
	params->targetFitness = TARGETFITNESS;
	params->updateFrequency = UPDATEFREQUENCY;

	_loadParametersFromFile(params, fileName, trainingData, testingData);

	return params;
}

//-----------------------------------------------------------------
//                          SETTERS
//-----------------------------------------------------------------

void _setMu(struct parameters *params, int mu) {
	if (mu > 0) {
		params->mu = mu;
	} else {
		printf(
				"\nWarning: mu value '%d' is invalid. Mu value must have a value of one or greater. Mu value left unchanged as '%d'.\n",
				mu, params->mu);
	}
}

void _setLambda(struct parameters *params, int lambda) {

	if (lambda > 0) {
		params->lambda = lambda;
	} else {
		printf(
				"\nWarning: lambda value '%d' is invalid. Lambda value must have a value of one or greater. Lambda value left unchanged as '%d'.\n",
				lambda, params->lambda);
	}
}

void _setEvolutionaryStrategy(struct parameters *params,
		char evolutionaryStrategy) {

	if (evolutionaryStrategy == '+' || evolutionaryStrategy == ',') {
		params->evolutionaryStrategy = evolutionaryStrategy;
	} else {
		printf(
				"\nWarning: the evolutionary strategy '%c' is invalid. The evolutionary strategy must be '+' or ','. The evolutionary strategy has been left unchanged as '%c'.\n",
				evolutionaryStrategy, params->evolutionaryStrategy);
	}
}

void _setMutationRate(struct parameters *params, double mutationRate) {

	if (mutationRate >= 0 && mutationRate <= 1) {
		params->mutationRate = mutationRate;
	} else {
		printf(
				"\nWarning: mutation rate '%f' is invalid. The mutation rate must be in the range [0,1]. The mutation rate has been left unchanged as '%f'.\n",
				mutationRate, params->mutationRate);
	}
}

void _setRecurrentConnectionProbability(struct parameters *params,
		double recurrentConnectionProbability) {

	if (recurrentConnectionProbability >= 0
			&& recurrentConnectionProbability <= 1) {
		params->recurrentConnectionProbability = recurrentConnectionProbability;
	} else {
		printf(
				"\nWarning: recurrent connection probability '%f' is invalid. The recurrent connection probability must be in the range [0,1]. The recurrent connection probability has been left unchanged as '%f'.\n",
				recurrentConnectionProbability,
				params->recurrentConnectionProbability);
	}
}

void _setNumInputs(struct parameters *params, int numInputs) {
	if (numInputs <= 0) {
		printf(
				"Error: number of chromosome inputs cannot be less than one; %d is invalid.\nTerminating.\n",
				numInputs);
		exit(0);
	}

	params->numInputs = numInputs;
}

void _setNumNodes(struct parameters *params, int numNodes) {
	if (numNodes < 0) {
		printf(
				"Error: number of chromosome nodes cannot be negative; %d is invalid.\nTerminating.\n",
				numNodes);
		exit(0);
	}

	params->numNodes = numNodes;
}

void _setNumOutputs(struct parameters *params, int numOutputs) {
	if (numOutputs < 0) {
		printf(
				"Error: number of chromosome outputs cannot be less than one; %d is invalid.\nTerminating.\n",
				numOutputs);
		exit(0);
	}

	params->numOutputs = numOutputs;
}

void _setArity(struct parameters *params, int arity) {
	if (arity < 0) {
		printf(
				"Error: node arity cannot be less than one; %d is invalid.\nTerminating.\n",
				arity);
		exit(0);
	}

	params->arity = arity;
}

void _setTargetFitness(struct parameters *params, double targetFitness) {
	params->targetFitness = targetFitness;
}

void _setUpdateFrequency(struct parameters *params, int updateFrequency) {
	if (updateFrequency < 0) {
		printf(
				"Warning: update frequency of %d is invalid. Update frequency must be >= 0. Update frequency is left unchanged as %d.\n",
				updateFrequency, params->updateFrequency);
	} else {
		params->updateFrequency = updateFrequency;
	}
}

void _setShortcutConnections(struct parameters *params, int shortcutConnections) {
	if (shortcutConnections == 0 || shortcutConnections == 1) {
		params->shortcutConnections = shortcutConnections;
	} else {
		printf(
				"\nWarning: shortcut connection '%d' is invalid. The shortcut connections takes values 0 or 1. The shortcut connection has been left unchanged as '%d'.\n",
				shortcutConnections, params->shortcutConnections);
	}
}

void _setConnectionWeightRange(struct parameters *params, double weightRange) {
	params->connectionWeightRange = weightRange;
}

//-----------------------------------------------------------------
//                          TOSTRING
//-----------------------------------------------------------------

void _printParameters(struct parameters *params) {
	if (params == NULL) {
		printf("Error: cannot print uninitialised parameters.\nTerminating.\n");
		exit(0);
	}

	printf("-----------------------------------------------------------\n");
	printf("                       Parameters                          \n");
	printf("-----------------------------------------------------------\n");
	printf("Evolutionary Strategy:\t\t\t(%d%c%d)-ES\n", params->mu,
			params->evolutionaryStrategy, params->lambda);
	printf("Inputs:\t\t\t\t\t%d\n", params->numInputs);
	printf("Nodes:\t\t\t\t\t%d\n", params->numNodes);
	printf("Outputs:\t\t\t\t%d\n", params->numOutputs);
	printf("Node Arity:\t\t\t\t%d\n", params->arity);
	printf("Connection weights range:\t\t+/- %f\n",
			params->connectionWeightRange);
	printf("Mutation Type:\t\t\t\t%s\n", params->mutationTypeName);
	printf("Mutation rate:\t\t\t\t%f\n", params->mutationRate);
	printf("Recurrent Connection Probability:\t%f\n",
			params->recurrentConnectionProbability);
	printf("Shortcut Connections:\t\t\t%d\n", params->shortcutConnections);
	printf("Fitness Function:\t\t\t%s\n", params->fitnessFunctionName);
	printf("Target Fitness:\t\t\t\t%f\n", params->targetFitness);
	printf("Selection scheme:\t\t\t%s\n", params->selectionSchemeName);
	printf("Reproduction scheme:\t\t\t%s\n", params->reproductionSchemeName);
	printf("Update frequency:\t\t\t%d\n", params->updateFrequency);
	_printFunctionSet(params);
	printf("-----------------------------------------------------------\n\n");
}

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeParameters(struct parameters *params) {
	if (params == NULL) {
		printf("Warning: double freeing of parameters prevented.\n");
		return;
	}

	free(params->funcSet);
	free(params);
}

//-----------------------------------------------------------------
//                          UTILITY
//-----------------------------------------------------------------

void _addNodeFunction(struct parameters *params, char const *functionNames) {
	char *pch;
	char functionNamesAsArray[FUNCTIONNAMELENGTH * FUNCTIONSETSIZE];

	strncpy(functionNamesAsArray, functionNames,
	FUNCTIONNAMELENGTH * FUNCTIONSETSIZE);

	//first function name
	pch = strtok(functionNamesAsArray, ", ");

	struct function *object;
	while (pch != NULL) {
		object = getFunction(pch);

		if (NULL != object) {
			_addCustomNodeFunction(params, object->mFunction,
					object->functionName, object->args);
		}

		//remove allocated object
		free(object);

		//DOC: Subsequent calls to get additional tokens from the same string
		//are indicated by passing a null pointer as the newstring argument
		pch = strtok(NULL, ", ");
	}

	if (params->funcSet->numFunctions == 0) {
		printf("Warning: No Functions added to function set.\n");
	}
}

void _addCustomNodeFunction(struct parameters *params,
		struct matrix* (*function)(const int numInputs, struct matrix **inputs,
				const double *weights, const double amplitude),
		char const *functionName, int maxNumInputs) {
	if (params->funcSet->numFunctions >= FUNCTIONSETSIZE) {
		printf(
				"Warning: functions set has reached maximum capacity (%d). Function '%s' not added.\n",
				FUNCTIONSETSIZE, functionName);
		return;
	}

	/* set the function name as the given function name */
	strncpy(params->funcSet->functionNames[params->funcSet->numFunctions],
			functionName, FUNCTIONNAMELENGTH);

	/* set the number of function inputs as the given number of function inputs */
	params->funcSet->maxNumInputs[params->funcSet->numFunctions] = maxNumInputs;

	/* add the given function to the function set */
	params->funcSet->mFunctions[params->funcSet->numFunctions] = function;

	params->funcSet->numFunctions++;
}

void _clearFunctionSet(struct parameters *params) {
	params->funcSet->numFunctions = 0;
}
