/*
 * stream.c
 *
 *  Created on: 16. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "stream.h"
#include <stdlib.h>
#include <stdio.h>

//-----------------------------------------------------------------
//                          WRITERS
//-----------------------------------------------------------------

void _saveChromosome(struct chromosome *chromo, char const *fileName) {
	int i;
	FILE *fp;

	fp = fopen(fileName, "w");

	if (fp == NULL) {
		printf(
				"Warning: cannot save chromosome to '%s'. Chromosome was not saved.\n",
				fileName);
		return;
	}

	fprintf(fp, "numInputs,%d\n", chromo->numInputs);
	fprintf(fp, "numNodes,%d\n", chromo->numNodes);
	fprintf(fp, "numOutputs,%d\n", chromo->numOutputs);
	fprintf(fp, "arity,%d\n", chromo->arity);

	fprintf(fp, "functionSet");

	for (i = 0; i < chromo->funcSet->numFunctions; i++) {
		fprintf(fp, ",%s", chromo->funcSet->functionNames[i]);
	}
	fprintf(fp, "\n");

	/* save the chromosome structure */
	for (i = 0; i < chromo->numNodes; i++) {
		fprintf(fp, "%d\n", chromo->nodes[i]->function);
	}

	for (i = 0; i < chromo->numOutputs; i++) {
		fprintf(fp, "%d,", chromo->outputNodes[i]);
	}

	fflush(fp);

	fclose(fp);
}
