/*
 * node.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "node.h"
#include <stdlib.h>
#include <stdio.h>

#include "chromosome.h"

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct node *_initialiseNode(int numInputs, int numNodes, int arity,
		int numFunctions, double recurrentConnectionProbability,
		int nodePosition) {
	struct node *n;
	int i;

	n = (struct node*) malloc(sizeof(struct node));
	n->inputs = (int*) malloc(arity * sizeof(int));
	n->function = _getRandomFunction(numFunctions);
	n->active = 1;

	for (i = 0; i < arity; i++) {
		n->inputs[i] = _getRandomNodeInput(numInputs, numNodes, nodePosition,
				recurrentConnectionProbability);
	}

	n->output = 0;
	n->maxArity = arity;

	return n;
}

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeNode(struct node *n) {
	if (n == NULL) {
		printf("Warning: double freeing of node prevented.\n");
		return;
	}

	free(n->inputs);
	free(n);
}

//-----------------------------------------------------------------
//                             UTILITY
//-----------------------------------------------------------------

void _copyNode(struct node *nodeDest, struct node *nodeSrc) {
	int i;

	nodeDest->function = nodeSrc->function;

	nodeDest->active = nodeSrc->active;

	nodeDest->maxArity = nodeSrc->maxArity;
	nodeDest->actArity = nodeSrc->actArity;

	for (i = 0; i < nodeSrc->maxArity; i++) {
		nodeDest->inputs[i] = nodeSrc->inputs[i];
	}
}
