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

	struct dataSet *data = initialiseMLDataSetFromFile("data/data_2.arff",
			"test");

	int numInputs = data->numInputs;
	int numNodes = NUM_NODES;
	int numOutputs = data->numOutputs;
	int nodeArity = NODE_ARITY;

	params = initialiseParameters(numInputs, numNodes, numOutputs, nodeArity);

	addNodeFunction(params, "head,last");

	chromo = initialiseChromosome(params);

	printChromosome(chromo, 1);

	executeChromosome(chromo, getDataSetSampleInputs(data, 0));

	printDataSet(data);

	saveChromosome(chromo, "data/chromosome.txt");

	freeChromosome(chromo);
	freeParameters(params);

	return 0;
}
