//
// Created by karlo on 13.12.2016..
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <float.h>

//-----------------------------------------------------------------
//                          INTERFACE
//-----------------------------------------------------------------
#include "cgp.h"

//-----------------------------------------------------------------
//                       DATA STRUCTURES
//-----------------------------------------------------------------
#include "node.h"
#include "dataset.h"
#include "functionset.h"
#include "parameters.h"
#include "chromosome.h"
#include "results.h"
#include "util.h"

//-----------------------------------------------------------------
//                        GA OPERATORS
//-----------------------------------------------------------------

#include "selection/selection.h"
#include "reproduction/reproduction.h"
#include "mutation/mutation.h"

//-----------------------------------------------------------------
//                         FITNESS
//-----------------------------------------------------------------

#include "fitness/fitness.h"

//-----------------------------------------------------------------
//                         STREAM
//-----------------------------------------------------------------

#include "stream/stream.h"

//-----------------------------------------------------------------
//                          INIT
//-----------------------------------------------------------------

struct parameters *initialiseParameters(const int numInputs, const int numNodes,
		const int numOutputs, const int arity) {
	return _initialiseParameters(numInputs, numNodes, numOutputs, arity);
}

struct parameters *initialiseParametersFromFile(char const *fileName,
		struct dataSet **trainingData, struct dataSet **testingData) {
	return _initialiseParametersFromFile(fileName, trainingData, testingData);
}

struct chromosome *initialiseChromosome(struct parameters *params) {
	return _initialiseChromosome(params);
}

struct chromosome *initialiseChromosomeFromChromosome(struct chromosome *chromo) {
	return _initialiseChromosomeFromChromosome(chromo);
}

struct chromosome *initialiseChromosomeFromFile(const char *file) {
	return _initialiseChromosomeFromFile(file);
}

struct dataSet *initialiseDataSetFromArrays(int numInputs, int numOutputs,
		int numSamples, double *inputs, double *outputs) {
	return _initialiseDataSetFromArrays(numInputs, numOutputs, numSamples,
			inputs, outputs);
}

struct dataSet *initialiseDataSetFromFile(char const *file) {
	return _initialiseDataSetFromFile(file);
}

struct dataSet *initialiseMLDataSetFromFile(char const *file, char const *param) {
	return _initialiseMLDataSetFromFile(file, param);
}

//-----------------------------------------------------------------
//                          DESTROY
//-----------------------------------------------------------------

void freeParameters(struct parameters *params) {
	_freeParameters(params);
}

void freeChromosome(struct chromosome *chromo) {
	_freeChromosome(chromo);
}

void freeResults(struct results *rels) {
	_freeResults(rels);
}

void freeDataSet(struct dataSet *data) {
	_freeDataSet(data);
}

//-----------------------------------------------------------------
//                          PRINT
//-----------------------------------------------------------------

void printChromosome(struct chromosome *chromo, int weights) {
	_printChromosome(chromo, weights);
}

void printPretty(struct chromosome *chromo, char const *fileName) {
	_savePrettyChromosome(chromo, fileName);
}

void printParameters(struct parameters *params) {
	_printParameters(params);
}

void printDataSet(struct dataSet *data) {
	_printDataSet(data);
}

void printMatrix(struct matrix *m) {
	_printMatrix(m);
}

//-----------------------------------------------------------------
//                          SAVER
//-----------------------------------------------------------------

void saveChromosome(struct chromosome *chromo, char const *fileName) {
	_saveChromosome(chromo, fileName);
}

void saveDataSet(struct dataSet *data, char const *fileName) {
	_saveDataSet(data, fileName);
}

void saveResults(struct results *rels, char const *fileName) {
	_saveResults(rels, fileName);
}

//-----------------------------------------------------------------
//                          COPY
//-----------------------------------------------------------------

void copyChromosome(struct chromosome *chromoDest, struct chromosome *chromoSrc) {
	_copyChromosome(chromoDest, chromoSrc);
}

//-----------------------------------------------------------------
//                          NODE METHODS
//-----------------------------------------------------------------

void addNodeFunction(struct parameters *params, char const *functionNames) {
	_addNodeFunction(params, functionNames);
}

void addCustomNodeFunction(struct parameters *params,
		struct matrix *(*function)(const int numInputs, struct matrix **inputs,
				const double *weights, const double amplitude),
		char const *functionName, int maxNumInputs) {
	_addCustomNodeFunction(params, function, functionName, maxNumInputs);
}

void clearFunctionSet(struct parameters *params) {
	_clearFunctionSet(params);
}

//-----------------------------------------------------------------
//                  		  GA
//-----------------------------------------------------------------

void mutateChromosome(struct parameters *params, struct chromosome *chromo) {
	_mutateChromosome(params, chromo);
}

void removeInactiveNodes(struct chromosome *chromo) {

}

//-----------------------------------------------------------------
//                  		EXECUTOR
//-----------------------------------------------------------------

void executeChromosome(struct chromosome *chromo, struct matrix **inputs) {
	_executeChromosome(chromo, inputs);
}

//-----------------------------------------------------------------
//                  		SETTERS
//-----------------------------------------------------------------

void setNumInputs(struct parameters *params, int numInputs) {
	_setNumInputs(params, numInputs);
}

void setNumNodes(struct parameters *params, int numNodes) {
	_setNumNodes(params, numNodes);
}

void setNumOutputs(struct parameters *params, int numOutputs) {
	_setNumOutputs(params, numOutputs);
}

void setArity(struct parameters *params, int arity) {
	_setArity(params, arity);
}

void setMu(struct parameters *params, int mu) {
	_setMu(params, mu);
}

void setLambda(struct parameters *params, int lambda) {
	_setLambda(params, lambda);
}

void setEvolutionaryStrategy(struct parameters *params,
		char evolutionaryStrategy) {
	_setEvolutionaryStrategy(params, evolutionaryStrategy);
}

void setMutationRate(struct parameters *params, double mutationRate) {
	_setMutationRate(params, mutationRate);
}

void setRecurrentConnectionProbability(struct parameters *params,
		double recurrentConnectionProbability) {
	_setRecurrentConnectionProbability(params, recurrentConnectionProbability);
}

void setShortcutConnections(struct parameters *params, int shortcutConnections) {
	_setShortcutConnections(params, shortcutConnections);
}

void setConnectionWeightRange(struct parameters *params, double weightRange) {
	_setConnectionWeightRange(params, weightRange);
}

void setCustomFitnessFunction(struct parameters *params,
		double (*fitnessFunction)(struct parameters *params,
				struct chromosome *chromo, struct dataSet *data,
				struct evaluator *eval), char const *fitnessFunctionName) {
	_setCustomFitnessFunction(params, fitnessFunction, fitnessFunctionName);
}

void setCustomSelectionScheme(struct parameters *params,
		void (*selectionScheme)(struct parameters *params,
				struct chromosome **parents,
				struct chromosome **candidateChromos, int numParents,
				int numCandidateChromos), char const *selectionSchemeName) {
	_setCustomSelectionScheme(params, selectionScheme, selectionSchemeName);
}

void setCustomReproductionScheme(struct parameters *params,
		void (*reproductionScheme)(struct parameters *params,
				struct chromosome **parents, struct chromosome **children,
				int numParents, int numChildren),
		char const *reproductionSchemeName) {
	_setCustomReproductionScheme(params, reproductionScheme,
			reproductionSchemeName);
}

void setChromosomeFitness(struct parameters *params, struct chromosome *chromo,
		struct dataSet *data, struct evaluator *eval) {
	_setChromosomeFitness(params, chromo, data, eval);
}

void resetChromosome(struct chromosome *chromo) {
	_resetChromosome(chromo);
}

void setTargetFitness(struct parameters *params, double targetFitness) {
	_setTargetFitness(params, targetFitness);
}

void setMutationType(struct parameters *params, char const *mutationType) {
	_setMutationType(params, mutationType);
}

void setUpdateFrequency(struct parameters *params, int updateFrequency) {
	_setUpdateFrequency(params, updateFrequency);
}

//-----------------------------------------------------------------
//                  		GETTERS
//-----------------------------------------------------------------

int getNumChromosomeInputs(struct chromosome *chromo) {
	return _getNumChromosomeInputs(chromo);
}

int getNumChromosomeNodes(struct chromosome *chromo) {
	return _getNumChromosomeNodes(chromo);
}

int getNumChromosomeActiveNodes(struct chromosome *chromo) {
	return _getNumChromosomeActiveNodes(chromo);
}

int getNumDataSetInputs(struct dataSet *data) {
	return _getNumDataSetInputs(data);
}

int getNumChromosomeOutputs(struct chromosome *chromo) {
	return _getNumChromosomeOutputs(chromo);
}

int getNumDataSetOutputs(struct dataSet *data) {
	return _getNumDataSetOutputs(data);
}

int getNumDataSetSamples(struct dataSet *data) {
	return _getNumDataSetSamples(data);
}

struct matrix *getChromosomeOutput(struct chromosome *chromo, int output) {
	return _getChromosomeOutput(chromo, output);
}

struct matrix *getChromosomeNodeValue(struct chromosome *chromo, int node) {
	return _getChromosomeNodeValue(chromo, node);
}

int isNodeActive(struct chromosome *chromo, int node) {
	return _isNodeActive(chromo, node);
}

double getDataSetSampleOutput(struct dataSet *data, int sample, int output) {
	return _getDataSetSampleOutput(data, sample, output);
}

struct matrix **getDataSetSampleInputs(struct dataSet *data, int sample) {
	return _getDataSetSampleInputs(data, sample);
}

struct matrix *getDataSetSampleInput(struct dataSet *data, int sample,
		int input) {
	return _getDataSetSampleInput(data, sample, input);
}

double *getDataSetSampleOutputs(struct dataSet *data, int sample) {
	return _getDataSetSampleOutputs(data, sample);
}

int getChromosomeNodeArity(struct chromosome *chromo, int index) {
	return _getChromosomeNodeArity(chromo, index);
}

double getChromosomeFitness(struct chromosome *chromo) {
	return _getChromosomeFitness(chromo);
}

int getNumChromosomeActiveConnections(struct chromosome *chromo) {
	return _getNumChromosomeActiveConnections(chromo);
}

int getChromosomeGenerations(struct chromosome *chromo) {
	return _getChromosomeGenerations(chromo);
}

int compareChromosomes(struct chromosome *chromoA, struct chromosome *chromoB) {
	return _compareChromosomes(chromoA, chromoB);
}

struct chromosome* getChromosome(struct results *rels, int run) {
	return _getChromosome(rels, run);
}

struct chromosome* getResultsBestChromosome(struct results *rels) {
	return _getResultsBestChromosome(rels);
}

int getNumChromosomes(struct results *rels) {
	return _getNumChromosomes(rels);
}

double getAverageFitness(struct results *rels) {
	return _getAverageFitness(rels);
}

double getMedianFitness(struct results *rels) {
	return _getMedianFitness(rels);
}

double getAverageActiveNodes(struct results *rels) {
	return _getAverageActiveNodes(rels);
}

//-----------------------------------------------------------------
//                  		UTILITY
//-----------------------------------------------------------------

void setRandomNumberSeed(unsigned int seed) {
	srand(seed);
}

//-----------------------------------------------------------------
//                  		CGP ENGINE
//-----------------------------------------------------------------

struct chromosome* runCGP(struct parameters *params, struct dataSet *data,
		int numGens) {

	int i;
	int gen;

	struct chromosome *bestChromo;

	struct chromosome **parentChromos;
	struct chromosome **childrenChromos;

	struct chromosome **candidateChromos;
	int numCandidateChromos;

	if (numGens < 0) {
		LOG(params,
				"Error: %d generations is invalid. The number of generations must be >= 0.\n Terminating.\n",
				numGens);
		exit(0);
	}

	if (data != NULL && params->numInputs != data->numInputs) {
		LOG(params,
				"Error: The number of inputs specified in the dataSet (%d) does not match the number of inputs specified in the parameters (%d).\n",
				data->numInputs, params->numInputs);
		LOG(params, "Terminating.\n");
		exit(0);
	}

	if (data != NULL && params->numOutputs != data->numOutputs) {
		LOG(params,
				"Error: The number of outputs specified in the dataSet (%d) does not match the number of outputs specified in the parameters (%d).\n",
				data->numOutputs, params->numOutputs);
		LOG(params, "Terminating.\n");
		exit(0);
	}

	parentChromos = (struct chromosome**) malloc(
			params->mu * sizeof(struct chromosome*));

	for (i = 0; i < params->mu; i++) {
		parentChromos[i] = initialiseChromosome(params);
	}

	childrenChromos = (struct chromosome**) malloc(
			params->lambda * sizeof(struct chromosome*));

	for (i = 0; i < params->lambda; i++) {
		childrenChromos[i] = initialiseChromosome(params);
	}

	bestChromo = initialiseChromosome(params);

	// Evolutionary Strategy
	if (params->evolutionaryStrategy == '+') {
		numCandidateChromos = params->mu + params->lambda;
	} else if (params->evolutionaryStrategy == ',') {
		numCandidateChromos = params->lambda;
	} else {
		printf(
				"Error: the evolutionary strategy '%c' is not known.\nTerminating.\n",
				params->evolutionaryStrategy);
		exit(0);
	}

	// initialise the candidateChromos
	candidateChromos = (struct chromosome**) malloc(
			numCandidateChromos * sizeof(struct chromosome*));

	for (i = 0; i < numCandidateChromos; i++) {
		candidateChromos[i] = initialiseChromosome(params);
	}

	// set fitness of the parents
	for (i = 0; i < params->mu; i++) {
		setChromosomeFitness(params, parentChromos[i], data, NULL);
	}

	// ECHO
	if (params->updateFrequency != 0) {
		LOG(params, "\n-- Starting CGP --\n\n");
		LOG(params, "Gen\tfitness\n");
	}

	int stagnation = 0;
	double bestStagnationSolution = 0;

	for (gen = 0; gen < numGens; gen++) {

		// set fitness of the children of the population
		for (i = 0; i < params->lambda; i++) {
			setChromosomeFitness(params, childrenChromos[i], data, NULL);
		}

		// get best chromosome
		_getBestChromosome(parentChromos, childrenChromos, params->mu,
				params->lambda, bestChromo);

		// check termination conditions
		if (getChromosomeFitness(bestChromo) <= params->targetFitness) {

			if (params->updateFrequency != 0) {
				LOG(params, "%d\t%f\t%d - Solution Found\n", gen,
						bestChromo->fitness, bestChromo->numActiveNodes);
			}

			break;
		}

		//check stagnation
		if (0 == stagnation
				|| (fabs(
						getChromosomeFitness(bestChromo)
								- bestStagnationSolution) < EPSILON)) {
			bestStagnationSolution = getChromosomeFitness(bestChromo);
			stagnation++;
		} else {
			stagnation = 0;
		}

		if (params->stagnation > 0 && stagnation == params->stagnation) {

			if (params->updateFrequency != 0) {
				LOG(params, "%d\t%f\t%d - Stagnation condition\n", gen,
						bestChromo->fitness, bestChromo->numActiveNodes);
			}

			break;
		}

		// display progress
		if (params->updateFrequency != 0
				&& (gen % params->updateFrequency == 0 || gen >= numGens - 1)) {
			LOG(params, "%d\t%f\t%d\n", gen, bestChromo->fitness,
					bestChromo->numActiveNodes);
		}

		if (params->evolutionaryStrategy == '+') {
			for (i = 0; i < numCandidateChromos; i++) {
				if (i < params->lambda) {
					copyChromosome(candidateChromos[i], childrenChromos[i]);
				} else {
					copyChromosome(candidateChromos[i],
							parentChromos[i - params->lambda]);
				}
			}
		} else if (params->evolutionaryStrategy == ',') {
			for (i = 0; i < numCandidateChromos; i++) {
				copyChromosome(candidateChromos[i], childrenChromos[i]);
			}
		}

		// select the parents from the candidateChromos
		params->selectionScheme(params, parentChromos, candidateChromos,
				params->mu, numCandidateChromos);

		// create the children from the parents
		params->reproductionScheme(params, parentChromos, childrenChromos,
				params->mu, params->lambda);
	}

	if (params->updateFrequency != 0) {
		printf("\n");
	}

	bestChromo->generation = gen;

	for (i = 0; i < params->mu; i++) {
		freeChromosome(parentChromos[i]);
	}
	free(parentChromos);

	for (i = 0; i < params->lambda; i++) {
		freeChromosome(childrenChromos[i]);
	}
	free(childrenChromos);

	for (i = 0; i < numCandidateChromos; i++) {
		freeChromosome(candidateChromos[i]);
	}
	free(candidateChromos);

	return bestChromo;
}

/**
 * Returns result structure for each run.
 * @param params
 * @param data
 * @param numGens
 * @param numRuns
 * @return
 */
struct results* repeatCGP(struct parameters *params, struct dataSet *data,
		int numGens, int numRuns) {
	int i;
	struct results *rels;

	rels = _initialiseResults(params, numRuns);

	for (i = 0; i < numRuns; i++) {
		LOG(params, "----Run %d----\n", i);

		rels->bestChromosomes[i] = runCGP(params, data, numGens);

		LOG(params, "Run\tFitness\t\tGenerations\tActive Nodes\n");

		LOG(params, "%d\t%f\t%d\t\t%d\n", i, rels->bestChromosomes[i]->fitness,
				rels->bestChromosomes[i]->generation,
				rels->bestChromosomes[i]->numActiveNodes);
	}

	LOG(params, "\n===RESULTS===\nRun\tFitness\t\tGenerations\tActive Nodes\n");

	for (i = 0; i < numRuns; i++) {
		LOG(params, "%d\t%f\t%d\t\t%d\n", i, rels->bestChromosomes[i]->fitness,
				rels->bestChromosomes[i]->generation,
				rels->bestChromosomes[i]->numActiveNodes);
	}

	LOG(params, "----------------------------------------------------\n");
	LOG(params, "MEAN\t%f\t%f\t%f\n", getAverageFitness(rels),
			_getAverageGenerations(rels), getAverageActiveNodes(rels));
	LOG(params, "MEDIAN\t%f\t%f\t%f\n", getMedianFitness(rels),
			_getMedianGenerations(rels), _getMedianActiveNodes(rels));
	LOG(params, "----------------------------------------------------\n\n");

	return rels;
}

