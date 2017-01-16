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
	struct chromosome *fittestChromosome = NULL;
	struct results *results = NULL;

	struct dataSet *trainingData = initialiseMLDataSetFromFile(
			"../data/data_2.arff", "test");

	int numInputs = trainingData->numInputs;
	int numNodes = NUM_NODES;
	int numOutputs = trainingData->numOutputs;
	int nodeArity = NODE_ARITY;

	params = initialiseParameters(numInputs, numNodes, numOutputs, nodeArity);

	addNodeFunction(params, getAllF());
	//setMutationType(params, "probabilisticActive");

	results = repeatCGP(params, trainingData, MAXGEN, MAXRUN);
	fittestChromosome = getResultsBestChromosome(results);

	printPretty(fittestChromosome, NULL);

	freeChromosome(fittestChromosome);
	freeResults(results);
	freeDataSet(trainingData);
	freeParameters(params);

	return 0;
}
