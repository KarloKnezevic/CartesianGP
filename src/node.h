/*
 * node.h
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef NODE_H_
#define NODE_H_

struct node {
	int function;

	int *inputs;

	int active;

	double output;

	int maxArity;

	int actArity;
};

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct node *_initialiseNode(int numInputs, int numNodes, int arity,
		int numFunctions, double recurrentConnectionProbability,
		int nodePosition);

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeNode(struct node *n);

//-----------------------------------------------------------------
//                             UTILITY
//-----------------------------------------------------------------

void _copyNode(struct node *nodeDest, struct node *nodeSrc);

#endif /* NODE_H_ */
