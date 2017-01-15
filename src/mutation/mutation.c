/*
 * mutation.c
 *
 *  Created on: 15. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "mutation.h"
#include "../util.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/**
 * Main idea: random node function, random node input, random node connection, random output
 * Mutation could be applied to all nodes and all connections (active or inactive)
 */
void probabilisticMutation(struct parameters *params, struct chromosome *chromo) {
	int i, j;

	//for every node in the chromosome
	for (i = 0; i < params->numNodes; i++) {

		//mutate the function gene
		if (_randDecimal() <= params->mutationRate) {
			chromo->nodes[i]->function = _getRandomFunction(
					chromo->funcSet->numFunctions);
		}

		//mutatate amplitude
		if (_randDecimal() <= params->mutationRate) {
			chromo->nodes[i]->amplitude = _getRandomAmplitude(
					params->amplitudeRange);
		}

		//for every input to each chromosome
		for (j = 0; j < params->arity; j++) {

			//mutate random node input
			if (_randDecimal() <= params->mutationRate) {
				chromo->nodes[i]->inputs[j] = _getRandomNodeInput(
						chromo->numInputs, chromo->numNodes, i,
						params->recurrentConnectionProbability);
			}

			//mutate the connection node
			if (_randDecimal() <= params->mutationRate) {
				chromo->nodes[i]->weights[j] = _getRandomConnection(
						params->connectionWeightRange);
			}
		}

	}

	//for every chromosome output
	for (i = 0; i < params->numOutputs; i++) {
		//mutate chromosome output
		if (_randDecimal() <= params->mutationRate) {
			chromo->outputNodes[i] = _getRandomChromosomeOutput(
					chromo->numInputs, chromo->numNodes,
					params->shortcutConnections);
		}
	}
}

/**
 * Same as probabilistic mutation, but only active nodes are mutated.
 * All chromosome outputs could be mutated.
 */
void probabilisticMutationOnlyActive(struct parameters *params,
		struct chromosome *chromo) {
	int i, j;
	int activeNode;

	//for every active node in the chromosome
	for (i = 0; i < chromo->numActiveNodes; i++) {

		activeNode = chromo->activeNodes[i];

		//mutate the function gene
		if (_randDecimal() <= params->mutationRate) {
			chromo->nodes[activeNode]->function = _getRandomFunction(
					chromo->funcSet->numFunctions);
		}

		//for every input to each chromosome
		for (j = 0; j < params->arity; j++) {

			//mutate the node input
			if (_randDecimal() <= params->mutationRate) {
				chromo->nodes[activeNode]->inputs[j] = _getRandomNodeInput(
						chromo->numInputs, chromo->numNodes, activeNode,
						params->recurrentConnectionProbability);
			}

			//mutate the node connection weight
			if (_randDecimal() <= params->mutationRate) {
				chromo->nodes[activeNode]->weights[j] = _getRandomConnection(
						params->connectionWeightRange);
			}
		}
	}

	//for every chromosome output
	for (i = 0; i < params->numOutputs; i++) {

		//mutate the chromosome output
		if (_randDecimal() <= params->mutationRate) {
			chromo->outputNodes[i] = _getRandomChromosomeOutput(
					chromo->numInputs, chromo->numNodes,
					params->shortcutConnections);
		}
	}
}

void singleMutation(struct parameters *params, struct chromosome *chromo) {
	int numFunctionGenes, numInputGenes, numOutputGenes;
	int numGenes;
	int geneToMutate;
	int nodeIndex;
	int nodeInputIndex;

	int mutatedActive = 0;
	int previousGeneValue;
	int newGeneValue;

	//get the number of each type of gene
	numFunctionGenes = params->numNodes;
	numInputGenes = params->numNodes * params->arity;
	numOutputGenes = params->numOutputs;

	//set the total number of chromosome genes
	numGenes = numFunctionGenes + numInputGenes + numOutputGenes;

	//while active gene not mutated
	while (mutatedActive == 0) {

		//select a random gene
		geneToMutate = _randInt(numGenes);

		//mutate function gene
		if (geneToMutate < numFunctionGenes) {
			nodeIndex = geneToMutate;
			previousGeneValue = chromo->nodes[nodeIndex]->function;
			chromo->nodes[nodeIndex]->function = _getRandomFunction(
					chromo->funcSet->numFunctions);
			newGeneValue = chromo->nodes[nodeIndex]->function;

			if ((previousGeneValue != newGeneValue)
					&& (chromo->nodes[nodeIndex]->active == 1)) {
				mutatedActive = 1;
			}

		}

		//mutate node input gene
		else if (geneToMutate < numFunctionGenes + numInputGenes) {
			nodeIndex =
					(int) ((geneToMutate - numFunctionGenes) / chromo->arity);
			nodeInputIndex = (geneToMutate - numFunctionGenes) % chromo->arity;

			previousGeneValue =
					chromo->nodes[nodeIndex]->inputs[nodeInputIndex];
			chromo->nodes[nodeIndex]->inputs[nodeInputIndex] =
					_getRandomNodeInput(chromo->numInputs, chromo->numNodes,
							nodeIndex, params->recurrentConnectionProbability);
			newGeneValue = chromo->nodes[nodeIndex]->inputs[nodeInputIndex];

			if ((previousGeneValue != newGeneValue)
					&& (chromo->nodes[nodeIndex]->active == 1)) {
				mutatedActive = 1;
			}
		}

		//mutate output gene
		else {
			nodeIndex = geneToMutate - numFunctionGenes - numInputGenes;
			previousGeneValue = chromo->outputNodes[nodeIndex];
			chromo->outputNodes[nodeIndex] = _getRandomChromosomeOutput(
					chromo->numInputs, chromo->numNodes,
					params->shortcutConnections);
			newGeneValue = chromo->outputNodes[nodeIndex];

			if (previousGeneValue != newGeneValue) {
				mutatedActive = 1;
			}
		}
	}
}

/**
 * Mutates numGenes * mutationrate genes.
 * Does not mutate weights.
 */
void pointMutation(struct parameters *params, struct chromosome *chromo) {
	int i;
	int numGenes;
	int numFunctionGenes, numInputGenes, numOutputGenes;
	int numGenesToMutate;
	int geneToMutate;
	int nodeIndex;
	int nodeInputIndex;

	numFunctionGenes = params->numNodes;
	numInputGenes = params->numNodes * params->arity;
	numOutputGenes = params->numOutputs;

	//set the total number of chromosome genes
	numGenes = numFunctionGenes + numInputGenes + numOutputGenes;

	//calculate the number of genes to mutate
	numGenesToMutate = (int) roundf(numGenes * params->mutationRate);

	//for the number of genes to mutate
	for (i = 0; i < numGenesToMutate; i++) {

		//select a random gene
		geneToMutate = _randInt(numGenes);

		//mutate function gene
		if (geneToMutate < numFunctionGenes) {
			nodeIndex = geneToMutate;
			chromo->nodes[nodeIndex]->function = _getRandomFunction(
					chromo->funcSet->numFunctions);
		} else if (geneToMutate < numFunctionGenes + numInputGenes) {
			nodeIndex =
					(int) ((geneToMutate - numFunctionGenes) / chromo->arity);
			nodeInputIndex = (geneToMutate - numFunctionGenes) % chromo->arity;
			chromo->nodes[nodeIndex]->inputs[nodeInputIndex] =
					_getRandomNodeInput(chromo->numInputs, chromo->numNodes,
							nodeIndex, params->recurrentConnectionProbability);
		} else {
			nodeIndex = geneToMutate - numFunctionGenes - numInputGenes;
			chromo->outputNodes[nodeIndex] = _getRandomChromosomeOutput(
					chromo->numInputs, chromo->numNodes,
					params->shortcutConnections);
		}
	}
}

/**
 *
 */
void pointMutationWeights(struct parameters *params, struct chromosome *chromo) {
	int i;
	int numGenes;
	int numFunctionGenes, numInputGenes, numWeightGenes, numOutputGenes;
	int numGenesToMutate;
	int geneToMutate;
	int nodeIndex;
	int nodeInputIndex;

	numFunctionGenes = params->numNodes;
	numInputGenes = params->numNodes * params->arity;
	numWeightGenes = params->numNodes * params->arity;
	numOutputGenes = params->numOutputs;

	//set the total number of chromosome genes
	numGenes = numFunctionGenes + numInputGenes + numWeightGenes
			+ numOutputGenes;

	//calculate the number of genes to mutate
	numGenesToMutate = (int) roundf(numGenes * params->mutationRate);

	//for the number of genes to mutate
	for (i = 0; i < numGenesToMutate; i++) {

		//select a random gene
		geneToMutate = _randInt(numGenes);

		//mutate function gene
		if (geneToMutate < numFunctionGenes) {
			nodeIndex = geneToMutate;
			chromo->nodes[nodeIndex]->function = _getRandomFunction(
					chromo->funcSet->numFunctions);
		}

		//mutate node input gene
		else if (geneToMutate < numFunctionGenes + numInputGenes) {

			nodeIndex =
					(int) ((geneToMutate - numFunctionGenes) / chromo->arity);
			nodeInputIndex = (geneToMutate - numFunctionGenes) % chromo->arity;

			chromo->nodes[nodeIndex]->inputs[nodeInputIndex] =
					_getRandomNodeInput(chromo->numInputs, chromo->numNodes,
							nodeIndex, params->recurrentConnectionProbability);
		}

		//mutate connection weight
		else if (geneToMutate
				< numFunctionGenes + numInputGenes + numWeightGenes) {

			nodeIndex = (int) ((geneToMutate - numFunctionGenes - numInputGenes)
					/ chromo->arity);
			nodeInputIndex = (geneToMutate - numFunctionGenes - numInputGenes)
					% chromo->arity;
			chromo->nodes[nodeIndex]->weights[nodeInputIndex] =
					_getRandomConnection(params->connectionWeightRange);
		}

		//mutate output gene
		else {
			nodeIndex = geneToMutate - numFunctionGenes - numInputGenes
					- numWeightGenes;
			chromo->outputNodes[nodeIndex] = _getRandomChromosomeOutput(
					chromo->numInputs, chromo->numNodes,
					params->shortcutConnections);
		}
	}
}

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setMutationType(struct parameters *params, char const *mutationType) {
	if (strncmp(mutationType, "probabilistic", MUTATIONTYPENAMELENGTH) == 0) {

		params->mutationType = probabilisticMutation;
		strncpy(params->mutationTypeName, "probabilistic",
		MUTATIONTYPENAMELENGTH);
	} else if (strncmp(mutationType, "probabilisticActive",
	MUTATIONTYPENAMELENGTH) == 0) {

		params->mutationType = probabilisticMutationOnlyActive;
		strncpy(params->mutationTypeName, "probabilisticActive",
		MUTATIONTYPENAMELENGTH);
	} else if (strncmp(mutationType, "single",
	MUTATIONTYPENAMELENGTH) == 0) {

		params->mutationType = singleMutation;
		strncpy(params->mutationTypeName, "single",
		MUTATIONTYPENAMELENGTH);
	} else if (strncmp(mutationType, "point",
	MUTATIONTYPENAMELENGTH) == 0) {

		params->mutationType = pointMutation;
		strncpy(params->mutationTypeName, "point",
		MUTATIONTYPENAMELENGTH);
	} else if (strncmp(mutationType, "pointWeight",
	MUTATIONTYPENAMELENGTH) == 0) {

		params->mutationType = pointMutationWeights;
		strncpy(params->mutationTypeName, "pointWeight",
		MUTATIONTYPENAMELENGTH);
	} else {
		printf(
				"\nWarning: mutation type '%s' is invalid. The mutation type must be 'probabilistic' or 'point'. The mutation type has been left unchanged as '%s'.\n",
				mutationType, params->mutationTypeName);
	}
}
