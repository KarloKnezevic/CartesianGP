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

	//TRAIN and TEST data

	struct dataSet *trainingData = initialiseMLDataSetFromFile(
			"data/data_2.arff", "train");

	struct dataSet *testingData = initialiseMLDataSetFromFile(
			"data/data_2.arff", "test");

	//PARAM SETUP

	int numInputs = trainingData->numInputs;
	int numNodes = NUM_NODES;
	int numOutputs = trainingData->numOutputs;
	int nodeArity = NODE_ARITY;

	params = initialiseParameters(numInputs, numNodes, numOutputs, nodeArity);

	//ADDITIONAL PARAM SETUP

	addNodeFunction(params, getAllF());
	//setMutationType(params, "probabilisticActive");

	//CGP RUN
	results = repeatCGP(params, trainingData, MAXGEN, MAXRUN);
	fittestChromosome = getResultsBestChromosome(results);

	//PRINT FITTEST
	printPretty(fittestChromosome, NULL);

	//TEST
	printf("\nTesting...\n");
	setChromosomeFitness(params, fittestChromosome, testingData);
	printf("Test data fitness: %f\n", fittestChromosome->fitness);

	freeChromosome(fittestChromosome);
	freeResults(results);
	freeDataSet(trainingData);
	freeDataSet(testingData);
	freeParameters(params);

	return 0;
}
