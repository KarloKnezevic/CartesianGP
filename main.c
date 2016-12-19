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

	int numInputs = 3;
	int numNodes = 5;
	int numOutputs = 2;
	int nodeArity = 2;

	params = initialiseParameters(numInputs, numNodes, numOutputs, nodeArity);

	addNodeFunction(params, "add,sub");

	chromo = initialiseChromosome(params);

//	chromo = initialiseChromosomeFromFile("data/chromosome.txt");

	printChromosome(chromo);

	saveChromosome(chromo, "data/copychromosome.txt");

	freeChromosome(chromo);
	freeParameters(params);

//	double d[] = {1,2,3,4};
//	struct matrix *m = _initialiseMatrixFromArray(1,4, d);
//
//	_printMatrix(m);


	return 0;
}
