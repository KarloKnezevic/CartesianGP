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
#include <string.h>

#include "../parameters.h"
#include "../functions/functions.h"

//-----------------------------------------------------------------
//                          READERS
//-----------------------------------------------------------------

struct chromosome* _loadChromosomeFromFile(char const *file) {
	int i, j;

	FILE *fp;
	struct chromosome *chromo;
	struct parameters *params;

	char *line, *record;
	char funcName[FUNCTIONNAMELENGTH];
	char buffer[1024];

	int numInputs, numNodes, numOutputs, arity;

	fp = fopen(file, "r");

	if (fp == NULL) {
		printf(
				"Warning: cannot open chromosome: '%s'. Chromosome was not open.\n",
				file);
		return NULL;
	}

	line = fgets(buffer, sizeof(buffer), fp);
	if (line == NULL) {
	}
	record = strtok(line, ",");
	record = strtok(NULL, ",");
	numInputs = atoi(record);

	line = fgets(buffer, sizeof(buffer), fp);
	if (line == NULL) {
	}
	record = strtok(line, ",");
	record = strtok(NULL, ",");
	numNodes = atoi(record);

	line = fgets(buffer, sizeof(buffer), fp);
	if (line == NULL) {
	}
	record = strtok(line, ",");
	record = strtok(NULL, ",");
	numOutputs = atoi(record);

	line = fgets(buffer, sizeof(buffer), fp);
	if (line == NULL) {
	}
	record = strtok(line, ",");
	record = strtok(NULL, ",");
	arity = atoi(record);

	params = _initialiseParameters(numInputs, numNodes, numOutputs, arity);

	line = fgets(buffer, sizeof(buffer), fp);
	if (line == NULL) {
	}
	record = strtok(line, ",\n");
	record = strtok(NULL, ",\n");

	while (record != NULL) {
		strncpy(funcName, record, FUNCTIONNAMELENGTH);

		struct function *object = getFunction(funcName);

		//only defined functions
		if (object == NULL) {
			printf(
					"Error: cannot load chromosome which contains custom node functions.\n");
			printf("Terminating.\n");
			_freeParameters(params);
			exit(0);
		} else {
			_addCustomNodeFunction(params, object->function,
					object->functionName, object->args);
		}

		record = strtok(NULL, ",\n");
	}

	chromo = _initialiseChromosome(params);

	for (i = 0; i < numNodes; i++) {

		line = fgets(buffer, sizeof(buffer), fp);
		record = strtok(line, ",\n");
		chromo->nodes[i]->function = atoi(record);

		for (j = 0; j < arity; j++) {
			line = fgets(buffer, sizeof(buffer), fp);
			sscanf(line, "%d", &chromo->nodes[i]->inputs[j]);
		}
	}

	line = fgets(buffer, sizeof(buffer), fp);
	record = strtok(line, ",\n");
	chromo->outputNodes[0] = atoi(record);

	for (i = 1; i < numOutputs; i++) {
		record = strtok(NULL, ",\n");
		chromo->outputNodes[i] = atoi(record);
	}

	fclose(fp);
	_freeParameters(params);

	_setChromosomeActiveNodes(chromo);

	return chromo;
}

//-----------------------------------------------------------------
//                          WRITERS
//-----------------------------------------------------------------

void _saveChromosome(struct chromosome *chromo, char const *fileName) {
	int i, j;
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

		for (j = 0; j < chromo->arity; j++) {
			fprintf(fp, "%d\n", chromo->nodes[i]->inputs[j]);
		}

	}

	for (i = 0; i < chromo->numOutputs; i++) {
		fprintf(fp, "%d,", chromo->outputNodes[i]);
	}

	fflush(fp);

	fclose(fp);
}
