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

	struct dataSet *trainingData = NULL;
	struct dataSet *testingData = NULL;

	//if input file
	if (2 == argc) {
		params = initialiseParametersFromFile(argv[1], &trainingData,
				&testingData);
	} else {
		if (__TEST__ != 1) {
			//RELEASE VERSION
			printf(
					"ERROR: path to parameters file must be given.\nTerminating...\n");
			return 0;
		}

		//TRAIN and TEST data
//		trainingData = initialiseMLDataSetFromFile("data/data_2.arff", "train");
//		testingData = initialiseMLDataSetFromFile("data/data_2.arff", "test");

		trainingData = _loadBCWDataSetFromFile(
				"data/breast-cancer-wisconsin.data", "train");
		testingData = _loadBCWDataSetFromFile(
				"data/breast-cancer-wisconsin.data", "test");

		//PARAM SETUP
		int numInputs = trainingData->numInputs;
		int numNodes = NUM_NODES;
		int numOutputs = trainingData->numOutputs;
		int nodeArity = NODE_ARITY;

		params = initialiseParameters(numInputs, numNodes, numOutputs,
				nodeArity);

		//ADDITIONAL PARAM SETUP
		addNodeFunction(params, getAllF());
	}

	//CGP RUN
	results = repeatCGP(params, trainingData, params->generations,
			params->runs);
	fittestChromosome = getResultsBestChromosome(results);

	//PRINT FITTEST
	printPretty(fittestChromosome, NULL);

	//TEST
	printf("\n\n---TESTING---\n");
	setChromosomeFitness(params, fittestChromosome, trainingData);
	printf("Test fitness: %f\n", fittestChromosome->fitness);

	//FREE
	freeChromosome(fittestChromosome);
	freeResults(results);
	freeDataSet(trainingData);
	freeDataSet(testingData);
	freeParameters(params);

	return 0;
}
