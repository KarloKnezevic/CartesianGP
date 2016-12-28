/*
 * main.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "main.h"

#include "src/math/lialg.h"

int main(int argc, char *argv[]) {

	struct parameters *params = NULL;
	struct chromosome *chromo = NULL;

	int numInputs = NUM_INPUT;
	int numNodes = NUM_NODES;
	int numOutputs = NUM_OUTPUT;
	int nodeArity = NODE_ARITY;

	params = initialiseParameters(numInputs, numNodes, numOutputs, nodeArity);

	addNodeFunction(params, "head,last");

	chromo = initialiseChromosome(params);

//	chromo = initialiseChromosomeFromFile("data/chromosome.txt");

	printChromosome(chromo, 1);

	double inputs[NUM_SAMPLES][NUM_INPUT];
	double outputs[NUM_SAMPLES][NUM_OUTPUT];

	setRandomNumberSeed(time(NULL));

	for (int i = 0; i < NUM_SAMPLES; i++) {
		double random = rand() % 10;
		inputs[i][0] = random;
		outputs[i][0] = inputs[i][0] >= 5 ? 1 : 0;
	}

	struct dataSet *data = initialiseDataSetFromArrays(numInputs, numOutputs,
	NUM_SAMPLES, inputs[0], outputs[0]);

	executeChromosome(chromo, getDataSetSampleInputs(data, 0));

	printDataSet(data);

//	saveChromosome(chromo, "data/chromosome.txt");

	freeChromosome(chromo);
	freeParameters(params);

	return 0;
}
