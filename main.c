/*
 * main.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "main.h"

int main(int argc, char *argv[]) {

	int i, gen;

	struct parameters *params = NULL;
	struct chromosome *population[POPULATIONSIZE];
	struct chromosome *fittestChromosome = NULL;
	struct dataSet *trainingData = initialiseMLDataSetFromFile(
			"data/data_2.arff", "train");

	int numInputs = trainingData->numInputs;
	int numNodes = trainingData->numInputs;
	int numOutputs = trainingData->numOutputs;
	int nodeArity = NODE_ARITY;

	params = initialiseParameters(numInputs, numNodes, numOutputs, nodeArity);

	addNodeFunction(params, getAllF());
	setMutationRate(params, 0.1);

	//init population
	for (i = 0; i < POPULATIONSIZE; i++) {
		population[i] = initialiseChromosome(params);
	}

	fittestChromosome = initialiseChromosome(params);

	//iterate generations
	for (gen = 0; gen < MAXGEN; gen++) {

		//set fitness
		for (i = 0; i < POPULATIONSIZE; i++) {
			setChromosomeFitness(params, population[i], trainingData);
		}

		//copy last chromosome to fittest
		copyChromosome(fittestChromosome, population[POPULATIONSIZE - 1]);

		//for all chromosomes except last
		for (i = 0; i < POPULATIONSIZE - 1; i++) {

			//check for better solution
			if (getChromosomeFitness(population[i])
					< getChromosomeFitness(fittestChromosome)) {
				copyChromosome(fittestChromosome, population[i]);
			}
		}

		//set the first member of population to be the fittest
		copyChromosome(population[0], fittestChromosome);

		for (i = 1; i < POPULATIONSIZE; i++) {
			copyChromosome(population[i], fittestChromosome);
			mutateChromosome(params, population[i]);
		}

		printf("gen\tfitness\n");
		printf("%d\t%f\n", gen, getChromosomeFitness(fittestChromosome));

	}

	for (i = 0; i < POPULATIONSIZE; i++) {
		freeChromosome(population[i]);
	}

	freeChromosome(fittestChromosome);
	freeDataSet(trainingData);
	freeParameters(params);

	return 0;
}
