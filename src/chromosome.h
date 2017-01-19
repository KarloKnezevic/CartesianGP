/*
 * chromosome.h
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef CHROMOSOME_H_
#define CHROMOSOME_H_

#include "node.h"
#include "functionset.h"
#include "dataset.h"
#include "math/lialg.h"

struct parameters;

struct chromosome {
	int numInputs;
	int numOutputs;
	int numNodes;

	int numActiveNodes;

	int arity;

	struct node **nodes;

	int *outputNodes;

	int *activeNodes;

	double fitness;

	struct matrix **outputValues;

	struct functionSet *funcSet;

	struct matrix **nodeInputsHold;

	int generation;

	int print;
};

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct chromosome *_initialiseChromosome(struct parameters *params);

struct chromosome *_initialiseChromosomeFromChromosome(
		struct chromosome *chromo);

struct chromosome *_initialiseChromosomeFromFile(const char *file);

//-----------------------------------------------------------------
//                            GETTERS
//-----------------------------------------------------------------

int _getChromosomeNodeArity(struct chromosome *chromo, int index);

double _getChromosomeFitness(struct chromosome *chromo);

int _getNumChromosomeActiveConnections(struct chromosome *chromo);

int _getChromosomeGenerations(struct chromosome *chromo);

int _getNumChromosomeNodes(struct chromosome *chromo);

int _getNumChromosomeActiveNodes(struct chromosome *chromo);

struct matrix *_getChromosomeNodeValue(struct chromosome *chromo, int node);

int _isNodeActive(struct chromosome *chromo, int node);

struct matrix *_getChromosomeOutput(struct chromosome *chromo, int output);

int _getNumChromosomeInputs(struct chromosome *chromo);

int _getNumChromosomeOutputs(struct chromosome *chromo);

void _getBestChromosome(struct chromosome **parents,
		struct chromosome **children, int numParents, int numChildren,
		struct chromosome *best);

//-----------------------------------------------------------------
//                            SETTERS
//-----------------------------------------------------------------

void _setChromosomeActiveNodes(struct chromosome *chromo);

void _setChromosomeFitness(struct parameters *params, struct chromosome *chromo,
		struct dataSet *data);

void _resetChromosome(struct chromosome *chromo);

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------




void _printChromosome(struct chromosome *chromo, int weights);

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeChromosome(struct chromosome *chromo);

//-----------------------------------------------------------------
//                              GA
//-----------------------------------------------------------------

void _mutateChromosome(struct parameters *params, struct chromosome *chromo);

void _removeInactiveNodes(struct chromosome *chromo);

//-----------------------------------------------------------------
//                           EXECUTOR
//-----------------------------------------------------------------

void _executeChromosome(struct chromosome *chromo, struct matrix **inputs);

//-----------------------------------------------------------------
//                             UTILITY
//-----------------------------------------------------------------

int _getRandomFunction(int numFunctions);

double _getRandomConnection(double weightRange);

double _getRandomAmplitude(double amplitudeRange);

int _getRandomNodeInput(int numChromoInputs, int numNodes, int nodePosition,
		double recurrentConnectionProbability);

int _getRandomChromosomeOutput(int numInputs, int numNodes,
		int shortcutConnections);

void _sortChromosomeArray(struct chromosome **chromoArray, int numChromos);

void _copyChromosome(struct chromosome *chromoDest,
		struct chromosome *chromoSrc);

int _compareChromosomes(struct chromosome *chromoA, struct chromosome *chromoB);

#endif /* CHROMOSOME_H_ */
