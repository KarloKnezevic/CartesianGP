/*
 * results.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "results.h"
#include <stdlib.h>

#include "chromosome.h"
#include "util.h"

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
