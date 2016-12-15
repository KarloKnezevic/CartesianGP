/*
 * main.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "main.h"

int main(int argc, char *argv[]) {

	struct parameters *params = NULL;
	struct chromosome *chromo = NULL;

	int numInputs = 15;
	int numNodes = 888;
	int numOutputs = 10;
	int nodeArity = 10;

	params = initialiseParameters(numInputs, numNodes, numOutputs, nodeArity);

	addNodeFunction(params, "add,sub,mul,div,sin");

	chromo = initialiseChromosome(params);

	printChromosome(chromo);

	freeChromosome(chromo);
	freeParameters(params);

	return 0;
}
