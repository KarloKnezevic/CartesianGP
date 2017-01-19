/*
 * parameters.h
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "dataset.h"
#include "chromosome.h"
#include "functionset.h"
#include "constants/constants.h"
#include "math/lialg.h"

struct parameters {
	int mu;
	int lambda;

	char evolutionaryStrategy;
	double mutationRate;

	double recurrentConnectionProbability;

	double connectionWeightRange;
	double amplitudeRange;

	int numInputs;
	int numNodes;
	int numOutputs;
	int arity;

	struct functionSet *funcSet;

	double targetFitness;

	int updateFrequency;
	int runs;
	int generations;

	int shortcutConnections;

	void (*mutationType)(struct parameters *params, struct chromosome *chromo);
	char mutationTypeName[MUTATIONTYPENAMELENGTH];

	double (*fitnessFunction)(struct parameters *params,
			struct chromosome *chromo, struct dataSet *dat);
	char fitnessFunctionName[FITNESSFUNCTIONNAMELENGTH];

	void (*selectionScheme)(struct parameters *params,
			struct chromosome **parents, struct chromosome **candidateChromos,
			int numParents, int numCandidateChromos);
	char selectionSchemeName[SELECTIONSCHEMENAMELENGTH];

	void (*reproductionScheme)(struct parameters *params,
			struct chromosome **parents, struct chromosome **children,
			int numParents, int numChildren);
	char reproductionSchemeName[REPRODUCTIONSCHEMENAMELENGTH];

	int print;
};

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------
struct parameters *_initialiseParameters(const int numInputs,
		const int numNodes, const int numOutputs, const int arity);

struct parameters *_initialiseParametersFromFile(char const *fileName,
		struct dataSet **trainingData, struct dataSet **testingData);

//-----------------------------------------------------------------
//                          SETTERS
//-----------------------------------------------------------------

void _setMu(struct parameters *params, int mu);
void _setLambda(struct parameters *params, int lambda);

void _setEvolutionaryStrategy(struct parameters *params,
		char evolutionaryStrategy);
void _setMutationRate(struct parameters *params, double mutationRate);

void _setRecurrentConnectionProbability(struct parameters *params,
		double recurrentConnectionProbability);

void _setNumInputs(struct parameters *params, int numInputs);
void _setNumNodes(struct parameters *params, int numNodes);
void _setNumOutputs(struct parameters *params, int numOutputs);
void _setArity(struct parameters *params, int arity);

void _setTargetFitness(struct parameters *params, double targetFitness);

void _setNumRuns(struct parameters *params, int numRuns);

void _setNumGenerations(struct parameters *params, int numGenerations);

void _setUpdateFrequency(struct parameters *params, int updateFrequency);

void _setShortcutConnections(struct parameters *params, int shortcutConnections);

void _setConnectionWeightRange(struct parameters *params, double weightRange);

void _setAmplitudeRange(struct parameters *params, double amplitudeRange);

//-----------------------------------------------------------------
//                          TOSTRING
//-----------------------------------------------------------------

void _printParameters(struct parameters *params);

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeParameters(struct parameters *params);

//-----------------------------------------------------------------
//                          UTILITY
//-----------------------------------------------------------------

void _addNodeFunction(struct parameters *params, char const *functionNames);

void _addCustomNodeFunction(struct parameters *params,
		struct matrix* (*function)(const int numInputs, struct matrix **inputs,
				const double *weights, const double amplitude),
		char const *functionName, int maxNumInputs);

void _clearFunctionSet(struct parameters *params);

#endif /* PARAMETERS_H_ */
