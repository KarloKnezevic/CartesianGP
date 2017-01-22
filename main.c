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
		//sca, breast-cancer ( data/breast-cancer-wisconsin.data )
		trainingData = _loadGenericMethodDataSetFromFile("sca",
				"data/noisy_e.dt", "train");
		testingData = _loadGenericMethodDataSetFromFile("sca",
				"data/noisy_e.dt", "test");

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

	//SAVE RESULTS
	saveResults(results, "stat.txt");

	//SAVE BEST CHROMO
	saveChromosome(fittestChromosome, "bestsolution.txt");
	printPretty(fittestChromosome, "hr_bestsolution.txt");

	//PRINT FITTEST
	printPretty(fittestChromosome, NULL);

	//TEST
	struct evaluator *eval = _initialiseEvaluator(params);
	setChromosomeFitness(params, fittestChromosome, testingData, eval);
	_printEvaluator(params, eval);

	//FREE
	_freeEvaluator(eval);
	freeChromosome(fittestChromosome);
	freeResults(results);
	freeDataSet(trainingData);
	freeDataSet(testingData);
	freeParameters(params);

	return 0;
}
