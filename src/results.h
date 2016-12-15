/*
 * results.h
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef RESULTS_H_
#define RESULTS_H_

#include "chromosome.h"
#include "parameters.h"

struct results {
	int numRuns;

	struct chromosome **bestChromosomes;
};

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct results* _initialiseResults(struct parameters *params, int numRuns);

//-----------------------------------------------------------------
//                            GETTERS
//-----------------------------------------------------------------

int _getNumChromosomes(struct results *rels);

double _getAverageFitness(struct results *rels);

double _getMedianFitness(struct results *rels);

double _getAverageActiveNodes(struct results *rels);

#endif /* RESULTS_H_ */
