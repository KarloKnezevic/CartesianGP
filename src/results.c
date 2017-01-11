/*
 * results.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "results.h"
#include <stdlib.h>
#include <stdio.h>

#include "chromosome.h"
#include "util.h"

#include "../CLan/memory.h"
#define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free( X, __FILE__, __LINE__, __FUNCTION__)

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------
struct results* _initialiseResults(struct parameters *params, int numRuns) {
	struct results *rels;

	rels = (struct results*) malloc(sizeof(struct results));
	rels->bestChromosomes = (struct chromosome**) malloc(
			numRuns * sizeof(struct chromosome*));

	rels->numRuns = numRuns;

	return rels;
}

//-----------------------------------------------------------------
//                            GETTERS
//-----------------------------------------------------------------

int _getNumChromosomes(struct results *rels) {
	return rels->numRuns;
}

double _getAverageFitness(struct results *rels) {
	int i;
	double avgFit = 0;
	struct chromosome *chromoTemp;

	for (i = 0; i < _getNumChromosomes(rels); i++) {
		chromoTemp = rels->bestChromosomes[i];
		avgFit += _getChromosomeFitness(chromoTemp);
	}

	avgFit = avgFit / _getNumChromosomes(rels);
	return avgFit;
}

double _getAverageGenerations(struct results *rels) {
	int i;
	double avgGens = 0;
	struct chromosome *chromoTemp;

	for (i = 0; i < _getNumChromosomes(rels); i++) {

		chromoTemp = rels->bestChromosomes[i];

		avgGens += _getChromosomeGenerations(chromoTemp);
	}

	avgGens = avgGens / _getNumChromosomes(rels);

	return avgGens;
}

double _getMedianFitness(struct results *rels) {
	int i;
	double med = 0;
	double *array = (double*) malloc(_getNumChromosomes(rels) * sizeof(double));

	for (i = 0; i < _getNumChromosomes(rels); i++) {
		array[i] = _getChromosomeFitness(rels->bestChromosomes[i]);
	}

	med = _medianDouble(array, _getNumChromosomes(rels));
	free(array);
	return med;
}

double _getMedianGenerations(struct results *rels) {
	int i;
	double med = 0;

	int *array = (int*) malloc(_getNumChromosomes(rels) * sizeof(int));

	for (i = 0; i < _getNumChromosomes(rels); i++) {
		array[i] = _getChromosomeGenerations(rels->bestChromosomes[i]);
	}

	med = _medianInt(array, _getNumChromosomes(rels));

	free(array);
	return med;
}

double _getMedianActiveNodes(struct results *rels) {
	int i;
	double medActiveNodes = 0;

	int *array = (int*) malloc(_getNumChromosomes(rels) * sizeof(int));

	for (i = 0; i < _getNumChromosomes(rels); i++) {
		array[i] = _getNumChromosomeActiveNodes(rels->bestChromosomes[i]);
	}

	medActiveNodes = _medianInt(array, _getNumChromosomes(rels));

	free(array);
	return medActiveNodes;
}

double _getAverageActiveNodes(struct results *rels) {
	int i;
	double avgActiveNodes = 0;
	struct chromosome *chromoTemp;

	for (i = 0; i < _getNumChromosomes(rels); i++) {
		chromoTemp = rels->bestChromosomes[i];
		avgActiveNodes += _getNumChromosomeActiveNodes(chromoTemp);
	}

	avgActiveNodes = avgActiveNodes / _getNumChromosomes(rels);
	return avgActiveNodes;
}

struct chromosome* _getChromosome(struct results *rels, int run) {
	struct chromosome *chromo;

	if (rels == NULL) {
		printf(
				"Error: cannot get best chromosome from uninitialised results.\nTerminating.\n");
		exit(0);
	}

	chromo = _initialiseChromosomeFromChromosome(rels->bestChromosomes[run]);

	return chromo;
}

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeResults(struct results *rels) {
	int i;

	if (rels == NULL) {
		printf("Warning: double freeing of results prevented.\n");
		return;
	}

	for (i = 0; i < rels->numRuns; i++) {
		_freeChromosome(rels->bestChromosomes[i]);
	}

	free(rels->bestChromosomes);
	free(rels);
}
