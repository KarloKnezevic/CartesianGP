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
#include "../math/lialg.h"

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
			sscanf(line, "%d,%lf", &chromo->nodes[i]->inputs[j], &chromo->nodes[i]->weights[j]);
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

/**
 * THIS FILE SHOULD BE CHANGED ACCORDING TO INPUT DATA.
 *
 * CONSIDER CHANGING DATASET OBJECT.
 */
struct dataSet *_loadDataSetFromFile(char const *file) {
	int i;
	struct dataSet *data;
	FILE *fp;
	char *line, *record;
	char buffer[1024];
	int lineNum = -1;
	int col;

	fp = fopen(file, "r");

	if (fp == NULL) {
		printf("Error: file '%s' cannot be found.\nTerminating.\n", file);
		exit(0);
	}

	data = (struct dataSet*) malloc(sizeof(struct dataSet));

	while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL) {

		//1st line is metadata: #inputs,#outputs,#samples
		if (lineNum == -1) {

			sscanf(line, "%d,%d,%d", &(data->numInputs), &(data->numOutputs),
					&(data->numSamples));

			data->inputData = (struct matrix ***) malloc(
					data->numSamples * sizeof(struct matrix*));
			data->outputData = (double**) malloc(
					data->numSamples * sizeof(double*));

			for (i = 0; i < data->numSamples; i++) {
				data->inputData[i] = (struct matrix **) malloc(
						data->numInputs * sizeof(struct matrix*));
				data->outputData[i] = (double*) malloc(
						data->numOutputs * sizeof(double));
			}
		} else {

			//first value
			record = strtok(line, " ,\n");
			col = 0;

			//until the end of line
			while (record != NULL) {
				if (col < data->numInputs) {
					data->inputData[lineNum][col] = _initialiseMatrixFromScalar(
							atof(record));
				} else {
					data->outputData[lineNum][col - data->numInputs] = atof(
							record);
				}

				record = strtok(NULL, " ,\n");
				col++;
			}
		}

		lineNum++;
	}

	fclose(fp);

	return data;
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
			fprintf(fp, "%d,%f\n", chromo->nodes[i]->inputs[j], chromo->nodes[i]->weights[j]);
		}

	}

	for (i = 0; i < chromo->numOutputs; i++) {
		fprintf(fp, "%d,", chromo->outputNodes[i]);
	}

	fflush(fp);

	fclose(fp);
}

void _saveDataSet(struct dataSet *data, char const *fileName) {
	int i, j;
	FILE *fp;

	fp = fopen(fileName, "w");

	if (fp == NULL) {
		printf("Warning: cannot save data set to %s. Data set was not saved.\n",
				fileName);
		return;
	}

	fprintf(fp, "%d,", data->numInputs);
	fprintf(fp, "%d,", data->numOutputs);
	fprintf(fp, "%d,", data->numSamples);
	fprintf(fp, "\n");

	for (i = 0; i < data->numSamples; i++) {
		for (j = 0; j < data->numInputs; j++) {
			fprintf(fp, "%f,", _getMatrixAsScalar(data->inputData[i][j]));
		}

		for (j = 0; j < data->numOutputs; j++) {
			fprintf(fp, "%f,", data->outputData[i][j]);
		}

		fprintf(fp, "\n");
	}

	fflush(fp);

	fclose(fp);
}

/**
 * CONSIDER CHANGING THIS METHOD ACCORDING TO NEEDS.
 */
void _saveResults(struct results *rels, char const *fileName) {
	FILE *fp;
	int i;

	struct chromosome *chromoTemp;

	if (rels == NULL) {
		printf(
				"Warning: cannot save uninitialised results structure. Results not saved.\n");
		return;
	}

	fp = fopen(fileName, "w");

	if (fp == NULL) {
		printf(
				"Warning: cannot open '%s' and so cannot save results to that file. Results not saved.\n",
				fileName);
		return;
	}

	fprintf(fp, "Run,Fitness,Generations,Active Nodes\n");

	for (i = 0; i < rels->numRuns; i++) {
		chromoTemp = _getChromosome(rels, i);

		fprintf(fp, "%d,%f,%d,%d\n", i, chromoTemp->fitness,
				chromoTemp->generation, chromoTemp->numActiveNodes);

		_freeChromosome(chromoTemp);
	}

	fflush(fp);

	fclose(fp);
}
