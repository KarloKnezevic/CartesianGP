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

struct parameters {
	int mu;
	int lambda;

	char evolutionaryStrategy;
	double mutationRate;

	double recurrentConnectionProbability;

	int numInputs;
	int numNodes;
	int numOutputs;
	int arity;

	struct functionSet *funcSet;

	double targetFitness;

	int updateFrequency;

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
};

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------
struct parameters *_initialiseParameters(const int numInputs,
		const int numNodes, const int numOutputs, const int arity);

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

void _setUpdateFrequency(struct parameters *params, int updateFrequency);

void _setShortcutConnections(struct parameters *params, int shortcutConnections);

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
		double (*function)(const int numInputs, const double *inputs),
		char const *functionName, int maxNumInputs);

void _clearFunctionSet(struct parameters *params);

#endif /* PARAMETERS_H_ */
