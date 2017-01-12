/*
 * chromosome.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "chromosome.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "util.h"
#include "parameters.h"
#include "stream/stream.h"

#include "../CLan/memory.h"
#define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free( X, __FILE__, __LINE__, __FUNCTION__)

void recursivelySetActiveNodes(struct chromosome *chromo, int nodeIndex);

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct chromosome *_initialiseChromosome(struct parameters *params) {
	struct chromosome *chromo;
	int i;

	if (params->funcSet->numFunctions < 1) {
		printf(
				"Error: chromosome not initialised due to empty functionSet.\nTerminating.\n");
		exit(0);
	}

	chromo = (struct chromosome*) malloc(sizeof(struct chromosome));
	chromo->nodes = (struct node**) malloc(
			params->numNodes * sizeof(struct node*));
	chromo->outputNodes = (int*) malloc(params->numOutputs * sizeof(int));
	chromo->activeNodes = (int*) malloc(params->numNodes * sizeof(int));
	chromo->outputValues = (struct matrix **) malloc(
			params->numOutputs * sizeof(struct matrix*));
	for (i = 0; i < params->numOutputs; i++) {
		chromo->outputValues[i] = NULL;
	}

	for (i = 0; i < params->numNodes; i++) {
		chromo->nodes[i] = _initialiseNode(params->numInputs, params->numNodes,
				params->arity, params->funcSet->numFunctions,
				params->connectionWeightRange,
				params->recurrentConnectionProbability, i);
	}

	for (i = 0; i < params->numOutputs; i++) {
		chromo->outputNodes[i] = _getRandomChromosomeOutput(params->numInputs,
				params->numNodes, params->shortcutConnections);
	}

	chromo->numInputs = params->numInputs;
	chromo->numNodes = params->numNodes;
	chromo->numOutputs = params->numOutputs;
	chromo->arity = params->arity;

	chromo->numActiveNodes = params->numNodes;

	//initial fitness
	chromo->fitness = -1;

	chromo->funcSet = (struct functionSet*) malloc(sizeof(struct functionSet));
	_copyFunctionSet(chromo->funcSet, params->funcSet);

	_setChromosomeActiveNodes(chromo);

	//init to NULL
	chromo->nodeInputsHold = (struct matrix**) malloc(
			params->arity * sizeof(struct matrix*));
	for (i = 0; i < params->arity; i++) {
		chromo->nodeInputsHold[i] = NULL;
	}

	return chromo;
}

struct chromosome *_initialiseChromosomeFromChromosome(
		struct chromosome *chromo) {
	struct chromosome *chromoNew;
	int i;

	if (chromo == NULL) {
		printf(
				"Error: cannot initialise chromosome from uninitialised chromosome.\nTerminating.\n");
		exit(0);
	}

	chromoNew = (struct chromosome*) malloc(sizeof(struct chromosome));

	chromoNew->nodes = (struct node**) malloc(
			chromo->numNodes * sizeof(struct node*));

	chromoNew->outputNodes = (int*) malloc(chromo->numOutputs * sizeof(int));

	chromoNew->activeNodes = (int*) malloc(chromo->numNodes * sizeof(int));

	chromoNew->outputValues = (struct matrix**) malloc(
			chromo->numOutputs * sizeof(struct matrix*));

	for (i = 0; i < chromo->numNodes; i++) {
		chromoNew->nodes[i] = _initialiseNode(chromo->numInputs,
				chromo->numNodes, chromo->arity, chromo->funcSet->numFunctions,
				0, 0, i);
		_copyNode(chromoNew->nodes[i], chromo->nodes[i]);
	}

	for (i = 0; i < chromo->numOutputs; i++) {
		chromoNew->outputNodes[i] = chromo->outputNodes[i];
	}

	chromoNew->numInputs = chromo->numInputs;
	chromoNew->numNodes = chromo->numNodes;
	chromoNew->numOutputs = chromo->numOutputs;
	chromoNew->arity = chromo->arity;

	chromoNew->fitness = chromo->fitness;

	chromoNew->generation = chromo->generation;

	chromoNew->funcSet = (struct functionSet*) malloc(
			sizeof(struct functionSet));
	_copyFunctionSet(chromoNew->funcSet, chromo->funcSet);

	_setChromosomeActiveNodes(chromoNew);

	chromoNew->nodeInputsHold = (struct matrix **) malloc(
			chromo->arity * sizeof(struct matrix *));

	return chromoNew;
}

struct chromosome *_initialiseChromosomeFromFile(const char *file) {
	return _loadChromosomeFromFile(file);
}

//-----------------------------------------------------------------
//                            GETTERS
//-----------------------------------------------------------------

int _getChromosomeNodeArity(struct chromosome *chromo, int index) {
	int chromoArity = chromo->arity;
	int maxArity = chromo->funcSet->maxNumInputs[chromo->nodes[index]->function];

	if (maxArity == -1) {
		return chromoArity;
	} else if (maxArity < chromoArity) {
		return maxArity;
	} else {
		return chromoArity;
	}
}

double _getChromosomeFitness(struct chromosome *chromo) {
	return chromo->fitness;
}

int _getNumChromosomeActiveConnections(struct chromosome *chromo) {
	int i;
	int complexity = 0;

	for (i = 0; i < chromo->numActiveNodes; i++) {
		complexity += chromo->nodes[chromo->activeNodes[i]]->actArity;
	}

	return complexity;
}

int _getChromosomeGenerations(struct chromosome *chromo) {
	return chromo->generation;
}

int _getNumChromosomeNodes(struct chromosome *chromo) {
	return chromo->numNodes;
}

int _getNumChromosomeActiveNodes(struct chromosome *chromo) {
	return chromo->numActiveNodes;
}

struct matrix *_getChromosomeNodeValue(struct chromosome *chromo, int node) {
	if (node < 0 || node > chromo->numNodes) {
		printf(
				"Error: node less than or greater than the number of nodes  in chromosome. Called from getChromosomeNodeValue.\n");
		exit(0);
	}

	return chromo->nodes[node]->output;
}

int _isNodeActive(struct chromosome *chromo, int node) {
	if (node < 0 || node > chromo->numNodes) {
		printf(
				"Error: node less than or greater than the number of nodes  in chromosome. Called from isNodeActive.\n");
		exit(0);
	}

	return chromo->nodes[node]->active;
}

struct matrix *_getChromosomeOutput(struct chromosome *chromo, int output) {
	if (output < 0 || output > chromo->numOutputs) {
		printf(
				"Error: output less than or greater than the number of chromosome outputs. Called from getChromosomeOutput.\n");
		exit(0);
	}

	return chromo->outputValues[output];
}

int _getNumChromosomeInputs(struct chromosome *chromo) {
	return chromo->numInputs;
}

int _getNumChromosomeOutputs(struct chromosome *chromo) {
	return chromo->numOutputs;
}

void _getBestChromosome(struct chromosome **parents,
		struct chromosome **children, int numParents, int numChildren,
		struct chromosome *best) {
	int i;
	struct chromosome *bestChromoSoFar;

	bestChromoSoFar = parents[0];

	for (i = 1; i < numParents; i++) {

		if (parents[i]->fitness <= bestChromoSoFar->fitness) {
			bestChromoSoFar = parents[i];
		}
	}

	for (i = 0; i < numChildren; i++) {

		if (children[i]->fitness <= bestChromoSoFar->fitness) {
			bestChromoSoFar = children[i];
		}
	}

	_copyChromosome(best, bestChromoSoFar);
}

//-----------------------------------------------------------------
//                            SETTERS
//-----------------------------------------------------------------

void _setChromosomeActiveNodes(struct chromosome *chromo) {
	int i;

	if (chromo == NULL) {
		printf(
				"Error: chromosome has not been initialised and so the active nodes cannot be set.\n");
		return;
	}

	chromo->numActiveNodes = 0;

	// reset active nodes
	for (i = 0; i < chromo->numNodes; i++) {
		chromo->nodes[i]->active = 0;
	}

	//recursive search from output to input
	for (i = 0; i < chromo->numOutputs; i++) {

		//if output connects to input, continue
		if (chromo->outputNodes[i] < chromo->numInputs) {
			continue;
		}

		//recursive search for active nodes
		recursivelySetActiveNodes(chromo, chromo->outputNodes[i]);

	}

	//place active nodes in order
	_sortIntArray(chromo->activeNodes, chromo->numActiveNodes);
}

void _setChromosomeFitness(struct parameters *params, struct chromosome *chromo,
		struct dataSet *data) {
	double fitness;

	_setChromosomeActiveNodes(chromo);
	fitness = params->fitnessFunction(params, chromo, data);
	chromo->fitness = fitness;
}

void _resetChromosome(struct chromosome *chromo) {
	int i;

	for (i = 0; i < chromo->numNodes; i++) {
		_freeMatrix(chromo->nodes[i]->output);
		chromo->nodes[i]->output = _initialiseMatrixFromScalar(0);
	}

	for (i = 0; i < chromo->numOutputs; i++) {
		_freeMatrix(chromo->outputValues[i]);
		chromo->outputValues[i] = NULL;
	}

	for (i = 0; i < chromo->arity; i++) {
		_freeMatrix(chromo->nodeInputsHold[i]);
		chromo->nodeInputsHold[i] = NULL;
	}
}

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printChromosome(struct chromosome *chromo, int weights) {
	int i, j;

	if (chromo == NULL) {
		printf(
				"Error: chromosome has not been initialised and cannot be printed.\n");
		return;
	}

	_setChromosomeActiveNodes(chromo);

	for (i = 0; i < chromo->numInputs; i++) {
		printf("(%d):\tinput\n", i);
	}

	for (i = 0; i < chromo->numNodes; i++) {

		printf("(%d):\t%s\t", chromo->numInputs + i,
				chromo->funcSet->functionNames[chromo->nodes[i]->function]);

		for (j = 0; j < _getChromosomeNodeArity(chromo, i); j++) {
			if (weights == 1) {
				printf("%d,%+.1f\t", chromo->nodes[i]->inputs[j],
						chromo->nodes[i]->weights[j]);
			} else {
				printf("%d ", chromo->nodes[i]->inputs[j]);
			}

		}

		if (chromo->nodes[i]->active == 1) {
			printf("*");
		}

		printf("\n");
	}

	printf("outputs: ");
	for (i = 0; i < chromo->numOutputs; i++) {

		printf("%d ", chromo->outputNodes[i]);
	}

	printf("\n\n");
}

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeChromosome(struct chromosome *chromo) {
	int i;

	if (chromo == NULL) {
		printf("Warning: double freeing of chromosome prevented.\n");
		return;
	}

	for (i = 0; i < chromo->numNodes; i++) {
		_freeNode(chromo->nodes[i]);
	}

	for (i = 0; i < chromo->numOutputs; i++) {
		_freeMatrix(chromo->outputValues[i]);
		chromo->outputValues[i] = NULL;
	}

	for (i = 0; i < chromo->arity; i++) {
		_freeMatrix(chromo->nodeInputsHold[i]);
	}

	free(chromo->nodeInputsHold);
	free(chromo->funcSet);
	free(chromo->outputValues);
	free(chromo->nodes);
	free(chromo->outputNodes);
	free(chromo->activeNodes);
	free(chromo);
}

//-----------------------------------------------------------------
//                              GA
//-----------------------------------------------------------------

void _mutateChromosome(struct parameters *params, struct chromosome *chromo) {
	params->mutationType(params, chromo);

	_setChromosomeActiveNodes(chromo);
}

void _removeInactiveNodes(struct chromosome *chromo) {
	int i, j, k;

	int originalNumNodes = chromo->numNodes;
	_setChromosomeActiveNodes(chromo);

	for (i = 0; i < chromo->numNodes - 1; i++) {
		if (chromo->nodes[i]->active == 0) {

			// set the node to be the next node
			for (j = i; j < chromo->numNodes - 1; j++) {
				_copyNode(chromo->nodes[j], chromo->nodes[j + 1]);
			}

			for (j = 0; j < chromo->numNodes; j++) {
				for (k = 0; k < chromo->arity; k++) {

					if (chromo->nodes[j]->inputs[k] >= i + chromo->numInputs) {
						chromo->nodes[j]->inputs[k]--;
					}
				}
			}

			for (j = 0; j < chromo->numOutputs; j++) {
				if (chromo->outputNodes[j] >= i + chromo->numInputs) {
					chromo->outputNodes[j]--;
				}
			}

			chromo->numNodes--;
			i--;
		}
	}

	for (i = chromo->numNodes; i < originalNumNodes; i++) {
		_freeNode(chromo->nodes[i]);
	}

	if (chromo->nodes[chromo->numNodes - 1]->active == 0) {
		_freeNode(chromo->nodes[chromo->numNodes - 1]);
		chromo->numNodes--;
	}

	chromo->nodes = (struct node**) realloc(chromo->nodes,
			chromo->numNodes * sizeof(struct node*));
	chromo->activeNodes = (int*) realloc(chromo->activeNodes,
			chromo->numNodes * sizeof(int));

	_setChromosomeActiveNodes(chromo);
}

//-----------------------------------------------------------------
//                           EXECUTOR
//-----------------------------------------------------------------

void _executeChromosome(struct chromosome *chromo, struct matrix **inputs) {
	int i, j;
	int nodeInputLocation;
	int currentActiveNode;
	int currentActiveNodeFunction;
	int nodeArity;

	_resetChromosome(chromo);

	const int numInputs = chromo->numInputs;
	const int numActiveNodes = chromo->numActiveNodes;
	const int numOutputs = chromo->numOutputs;

	if (chromo == NULL) {
		printf(
				"Error: cannot execute uninitialised chromosome.\n Terminating.\n");
		exit(0);
	}

	//for all active nodes
	for (i = 0; i < numActiveNodes; i++) {

		//get index of current active node
		currentActiveNode = chromo->activeNodes[i];

		nodeArity = chromo->nodes[currentActiveNode]->actArity;

		//for each input
		for (j = 0; j < nodeArity; j++) {

			//node input locations
			nodeInputLocation = chromo->nodes[currentActiveNode]->inputs[j];

			//INPUT NODES
			if (nodeInputLocation < numInputs) {
				if (chromo->nodeInputsHold[j] != NULL) {
					_freeMatrix(chromo->nodeInputsHold[j]);
				}

				chromo->nodeInputsHold[j] = _copyMatrixOf(
						inputs[nodeInputLocation]);
			} else {
				if (chromo->nodeInputsHold[j] != NULL) {
					_freeMatrix(chromo->nodeInputsHold[j]);
				}
				//INTERNAL NODE
				chromo->nodeInputsHold[j] = _copyMatrixOf(
						chromo->nodes[nodeInputLocation - numInputs]->output);
			}
		}

		//get active function
		currentActiveNodeFunction = chromo->nodes[currentActiveNode]->function;

		//release previous solution
		_freeMatrix(chromo->nodes[currentActiveNode]->output);

		//calculate output of active function -> call delegate method
		chromo->nodes[currentActiveNode]->output =
				chromo->funcSet->mFunctions[currentActiveNodeFunction](
						nodeArity, chromo->nodeInputsHold,
						chromo->nodes[currentActiveNode]->weights);

		_checkMatrixForNaN(chromo->nodes[currentActiveNode]->output, 0);

		_checkMatrixForInf(chromo->nodes[currentActiveNode]->output);
	}

	//set chromosome output
	for (i = 0; i < numOutputs; i++) {

		//output node is connected to input node
		if (chromo->outputNodes[i] < numInputs) {
			if (chromo->outputValues[i] != NULL) {
				_freeMatrix(chromo->outputValues[i]);
			}
			chromo->outputValues[i] = _copyMatrixOf(
					inputs[chromo->outputNodes[i]]);
		} else {
			if (chromo->outputValues[i] != NULL) {
				_freeMatrix(chromo->outputValues[i]);
			}
			//scaled because inner indexes are shifted in chromosome -> inputs not coded
			chromo->outputValues[i] = _copyMatrixOf(
					chromo->nodes[chromo->outputNodes[i] - numInputs]->output);
		}

	}

}

//-----------------------------------------------------------------
//                             UTILITY
//-----------------------------------------------------------------

int _getRandomFunction(int numFunctions) {
	if (numFunctions < 1) {
		printf(
				"Error: cannot assign the function gene a value as the Function Set is empty.\nTerminating.\n");
		exit(0);
	}

	return _randInt(numFunctions);
}

double _getRandomConnection(double weightRange) {
	return (_randDecimal() * 2 * weightRange) - weightRange;
}

int _getRandomNodeInput(int numChromoInputs, int numNodes, int nodePosition,
		double recurrentConnectionProbability) {
	int input;

	//pick any ahead node or node itself
	if (_randDecimal() <= recurrentConnectionProbability) {
		input = _randInt(numNodes - nodePosition) + nodePosition + 1;
	} else {
		//pick any previous node
		input = _randInt(numChromoInputs + nodePosition);
	}

	return input;
}

int _getRandomChromosomeOutput(int numInputs, int numNodes,
		int shortcutConnections) {
	int output;

	//input can be directly connected do output
	if (shortcutConnections == 1) {
		output = _randInt(numInputs + numNodes);
	} else {
		//only nodes output can be connected to output
		output = _randInt(numNodes) + numInputs;
	}

	return output;
}

void _sortChromosomeArray(struct chromosome **chromoArray, int numChromos) {
	int i, j;
	struct chromosome *chromoTmp;

	//selection sort
	for (i = 0; i < numChromos; i++) {
		for (j = i; j < numChromos; j++) {

			//natural order
			if (chromoArray[i]->fitness > chromoArray[j]->fitness) {
				chromoTmp = chromoArray[i];
				chromoArray[i] = chromoArray[j];
				chromoArray[j] = chromoTmp;
			}

		}
	}
}

void _copyChromosome(struct chromosome *chromoDest,
		struct chromosome *chromoSrc) {
	int i;

	if (chromoDest->numInputs != chromoSrc->numInputs) {
		printf(
				"Error: cannot copy a chromosome to a chromosome of different dimensions. The number of chromosome inputs do not match.\n");
		printf("Terminating.\n");
		exit(0);
	}

	if (chromoDest->numNodes != chromoSrc->numNodes) {
		printf(
				"Error: cannot copy a chromosome to a chromosome of different dimensions. The number of chromosome nodes do not match.\n");
		printf("Terminating.\n");
		exit(0);
	}

	if (chromoDest->numOutputs != chromoSrc->numOutputs) {
		printf(
				"Error: cannot copy a chromosome to a chromosome of different dimensions. The number of chromosome outputs do not match.\n");
		printf("Terminating.\n");
		exit(0);
	}

	if (chromoDest->arity != chromoSrc->arity) {
		printf(
				"Error: cannot copy a chromosome to a chromosome of different dimensions. The arity of the chromosome nodes do not match.\n");
		printf("Terminating.\n");
		exit(0);
	}

	for (i = 0; i < chromoSrc->numNodes; i++) {
		_copyNode(chromoDest->nodes[i], chromoSrc->nodes[i]);
		chromoDest->activeNodes[i] = chromoSrc->activeNodes[i];
	}

	_copyFunctionSet(chromoDest->funcSet, chromoSrc->funcSet);

	for (i = 0; i < chromoSrc->numOutputs; i++) {
		chromoDest->outputNodes[i] = chromoSrc->outputNodes[i];
	}

	chromoDest->numActiveNodes = chromoSrc->numActiveNodes;

	chromoDest->fitness = chromoSrc->fitness;

	chromoDest->generation = chromoSrc->generation;
}

void recursivelySetActiveNodes(struct chromosome *chromo, int nodeIndex) {
	int i;

	//if node is input node
	if (nodeIndex < chromo->numInputs) {
		return;
	}

	//if node has already been flagged as active
	if (chromo->nodes[nodeIndex - chromo->numInputs]->active == 1) {
		return;
	}

	//log the node as active
	chromo->nodes[nodeIndex - chromo->numInputs]->active = 1;
	chromo->activeNodes[chromo->numActiveNodes] = nodeIndex - chromo->numInputs;
	chromo->numActiveNodes++;

	//set actual arity
	chromo->nodes[nodeIndex - chromo->numInputs]->actArity =
			_getChromosomeNodeArity(chromo, nodeIndex - chromo->numInputs);

	//recursively log all connected nodes
	for (i = 0; i < chromo->nodes[nodeIndex - chromo->numInputs]->actArity;
			i++) {
		recursivelySetActiveNodes(chromo,
				chromo->nodes[nodeIndex - chromo->numInputs]->inputs[i]);
	}
}

int _compareChromosomes(struct chromosome *chromoA, struct chromosome *chromoB) {
	int i, j;

	if (chromoA == NULL || chromoB == NULL) {
		return 0;
	}

	if (chromoA->numInputs != chromoB->numInputs) {
		return 0;
	}

	if (chromoA->numNodes != chromoB->numNodes) {
		return 0;
	}

	if (chromoA->numOutputs != chromoB->numOutputs) {
		return 0;
	}

	if (chromoA->arity != chromoB->arity) {
		return 0;
	}

	for (i = 0; i < chromoA->numNodes; i++) {
		if (chromoA->nodes[i]->function != chromoB->nodes[i]->function) {
			return 0;
		}

		for (j = 0; j < chromoA->arity; j++) {
			if (chromoA->nodes[i]->inputs[j] != chromoB->nodes[i]->inputs[j]) {
				return 0;
			}
		}
	}

	for (i = 0; i < chromoA->numOutputs; i++) {
		if (chromoA->outputNodes[i] != chromoB->outputNodes[i]) {
			return 0;
		}
	}

	return 1;
}
