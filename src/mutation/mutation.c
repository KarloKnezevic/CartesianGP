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

void probabilisticMutation(struct parameters *params, struct chromosome *chromo) {
	int i, j;

	//for every node in the chromosome
	for (i = 0; i < params->numNodes; i++) {

		//mutate the function gene
		if (_randDecimal() <= params->mutationRate) {
			chromo->nodes[i]->function = _getRandomFunction(
					chromo->funcSet->numFunctions);
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

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setMutationType(struct parameters *params, char const *mutationType) {
	if (strncmp(mutationType, "probabilistic", MUTATIONTYPENAMELENGTH) == 0) {

		params->mutationType = probabilisticMutation;
		strncpy(params->mutationTypeName, "probabilistic",
		MUTATIONTYPENAMELENGTH);
	} else {
		printf(
				"\nWarning: mutation type '%s' is invalid. The mutation type must be 'probabilistic' or 'point'. The mutation type has been left unchanged as '%s'.\n",
				mutationType, params->mutationTypeName);
	}
}
