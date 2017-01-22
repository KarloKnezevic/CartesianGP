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

#include "impl/ParametersStreamImpl.h"
#include "impl/GenericStreamImpl.h"
#include "impl/SCAStreamImpl.h"
#include "impl/BCWStreamImpl.h"
#include "impl/DIPHCDStreamImpl.h"

//-----------------------------------------------------------------
//                       READERS FACTORY
//-----------------------------------------------------------------

struct dataSet *_loadGenericMethodDataSetFromFile(char const *method,
		char const *file, char const *param) {

	if (strncmp(method, "sca", PARSER_METHOD_LENGTH) == 0) {
		return _loadMLDataSetFromFile(file, param);
	} else if (strncmp(method, "breast-cancer",
	PARSER_METHOD_LENGTH) == 0) {
		return _loadBCWDataSetFromFile(file, param);
	} else if (strncmp(method, "bin",
	PARSER_METHOD_LENGTH) == 0) {
		return _loadDIPHBCDataSetFromFile(file, param);
	}

	//by default sca
	return _loadMLDataSetFromFile(file, param);
}

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
			_addCustomNodeFunction(params, object->mFunction,
					object->functionName, object->args);
		}

		record = strtok(NULL, ",\n");
	}

	chromo = _initialiseChromosome(params);

	for (i = 0; i < numNodes; i++) {

		line = fgets(buffer, sizeof(buffer), fp);
		sscanf(line, "%d,%lf", &chromo->nodes[i]->function,
				&chromo->nodes[i]->amplitude);

		for (j = 0; j < arity; j++) {
			line = fgets(buffer, sizeof(buffer), fp);
			sscanf(line, "%d,%lf", &chromo->nodes[i]->inputs[j],
					&chromo->nodes[i]->weights[j]);
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

struct dataSet *_loadDataSetFromFile(char const *file) {
	return _loadGenericFromStream(file);
}

struct dataSet *_loadMLDataSetFromFile(char const *file, char const *param) {
	return _loadSCAFromStream(file, param);
}

struct dataSet *_loadBCWDataSetFromFile(char const *file, char const *param) {
	return _loadBCWFromStream(file, param);
}

struct dataSet *_loadDIPHBCDataSetFromFile(char const *file, char const *param) {
	return _loadDIPHCDFromStream(file, param);
}

void _loadParametersFromFile(struct parameters *params, char const *file,
		struct dataSet **trainingData, struct dataSet **testingData) {
	return _loadParametersFromStream(params, file, trainingData, testingData);
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
		fprintf(fp, "%d,%f\n", chromo->nodes[i]->function,
				chromo->nodes[i]->amplitude);

		for (j = 0; j < chromo->arity; j++) {
			fprintf(fp, "%d,%f\n", chromo->nodes[i]->inputs[j],
					chromo->nodes[i]->weights[j]);
		}

	}

	for (i = 0; i < chromo->numOutputs; i++) {
		fprintf(fp, "%d,", chromo->outputNodes[i]);
	}

	fflush(fp);

	fclose(fp);
}

#define AMPLITUDE(string) "%.1f*" string
void _savePrettyChromosomeRecursive(struct chromosome *chromo, int index,
		FILE *fp) {

	int i;

	if (index < chromo->numInputs) {
		fprintf(fp, "x_%d", index);
		return;
	}

	//ADD
	if (strncmp(
			chromo->funcSet->functionNames[chromo->nodes[index
					- chromo->numInputs]->function], "add",
			FUNCTIONNAMELENGTH) == 0) {

		fprintf(fp, AMPLITUDE("("),
				chromo->nodes[index - chromo->numInputs]->amplitude);

		_savePrettyChromosomeRecursive(chromo,
				chromo->nodes[index - chromo->numInputs]->inputs[0], fp);

		for (i = 1;
				i < _getChromosomeNodeArity(chromo, index - chromo->numInputs);
				i++) {

			fprintf(fp, " + ");

			_savePrettyChromosomeRecursive(chromo,
					chromo->nodes[index - chromo->numInputs]->inputs[i], fp);
		}

		fprintf(fp, ")");
	}

	//SUB
	else if (strncmp(
			chromo->funcSet->functionNames[chromo->nodes[index
					- chromo->numInputs]->function], "sub",
			FUNCTIONNAMELENGTH) == 0) {

		fprintf(fp, AMPLITUDE("("),
				chromo->nodes[index - chromo->numInputs]->amplitude);

		_savePrettyChromosomeRecursive(chromo,
				chromo->nodes[index - chromo->numInputs]->inputs[0], fp);

		for (i = 1;
				i < _getChromosomeNodeArity(chromo, index - chromo->numInputs);
				i++) {

			fprintf(fp, " - ");

			_savePrettyChromosomeRecursive(chromo,
					chromo->nodes[index - chromo->numInputs]->inputs[i], fp);
		}

		fprintf(fp, ")");
	}

	//MUL
	else if (strncmp(
			chromo->funcSet->functionNames[chromo->nodes[index
					- chromo->numInputs]->function], "mul",
			FUNCTIONNAMELENGTH) == 0) {

		fprintf(fp, AMPLITUDE("("),
				chromo->nodes[index - chromo->numInputs]->amplitude);

		_savePrettyChromosomeRecursive(chromo,
				chromo->nodes[index - chromo->numInputs]->inputs[0], fp);

		for (i = 1;
				i < _getChromosomeNodeArity(chromo, index - chromo->numInputs);
				i++) {

			fprintf(fp, " * ");

			_savePrettyChromosomeRecursive(chromo,
					chromo->nodes[index - chromo->numInputs]->inputs[i], fp);
		}

		fprintf(fp, ")");
	}

	//DIV
	else if (strncmp(
			chromo->funcSet->functionNames[chromo->nodes[index
					- chromo->numInputs]->function], "div",
			FUNCTIONNAMELENGTH) == 0) {

		if (_getChromosomeNodeArity(chromo, index - chromo->numInputs) == 1) {
			_savePrettyChromosomeRecursive(chromo,
					chromo->nodes[index - chromo->numInputs]->inputs[0], fp);
		} else {

			for (i = 0;
					i
							< _getChromosomeNodeArity(chromo,
									index - chromo->numInputs); i++) {

				if (i + 1
						< _getChromosomeNodeArity(chromo,
								index - chromo->numInputs)) {
					fprintf(fp, AMPLITUDE("("),
							chromo->nodes[index - chromo->numInputs]->amplitude);
					_savePrettyChromosomeRecursive(chromo,
							chromo->nodes[index - chromo->numInputs]->inputs[i],
							fp);
					fprintf(fp, ") / (");
				} else if (i + 1
						== _getChromosomeNodeArity(chromo,
								index - chromo->numInputs)
						&& _getChromosomeNodeArity(chromo,
								index - chromo->numInputs) > 2) {
					_savePrettyChromosomeRecursive(chromo,
							chromo->nodes[index - chromo->numInputs]->inputs[i],
							fp);
					fprintf(fp, ")");
				} else {
					_savePrettyChromosomeRecursive(chromo,
							chromo->nodes[index - chromo->numInputs]->inputs[i],
							fp);
					fprintf(fp, ")");
				}
			}
		}
	}

	//ABS
	else if (strncmp(
			chromo->funcSet->functionNames[chromo->nodes[index
					- chromo->numInputs]->function], "abs",
			FUNCTIONNAMELENGTH) == 0) {

		fprintf(fp, AMPLITUDE("|"),
				chromo->nodes[index - chromo->numInputs]->amplitude);

		_savePrettyChromosomeRecursive(chromo,
				chromo->nodes[index - chromo->numInputs]->inputs[0], fp);

		fprintf(fp, " |");

	}

	//POW
	else if (strncmp(
			chromo->funcSet->functionNames[chromo->nodes[index
					- chromo->numInputs]->function], "pow",
			FUNCTIONNAMELENGTH) == 0) {

		fprintf(fp, AMPLITUDE("(("),
				chromo->nodes[index - chromo->numInputs]->amplitude);

		_savePrettyChromosomeRecursive(chromo,
				chromo->nodes[index - chromo->numInputs]->inputs[0], fp);

		fprintf(fp, " )^(");

		_savePrettyChromosomeRecursive(chromo,
				chromo->nodes[index - chromo->numInputs]->inputs[1], fp);

		fprintf(fp, " ))");

	}

	//POWINT
	else if (strncmp(
			chromo->funcSet->functionNames[chromo->nodes[index
					- chromo->numInputs]->function], "powint",
			FUNCTIONNAMELENGTH) == 0) {

		fprintf(fp, AMPLITUDE("(("),
				chromo->nodes[index - chromo->numInputs]->amplitude);

		_savePrettyChromosomeRecursive(chromo,
				chromo->nodes[index - chromo->numInputs]->inputs[0], fp);

		fprintf(fp, " )^(");

		_savePrettyChromosomeRecursive(chromo,
				chromo->nodes[index - chromo->numInputs]->inputs[1], fp);

		fprintf(fp, " ))");

	}

	//EXP
	else if (strncmp(
			chromo->funcSet->functionNames[chromo->nodes[index
					- chromo->numInputs]->function], "exp",
			FUNCTIONNAMELENGTH) == 0) {

		fprintf(fp, AMPLITUDE("e^("),
				chromo->nodes[index - chromo->numInputs]->amplitude);

		_savePrettyChromosomeRecursive(chromo,
				chromo->nodes[index - chromo->numInputs]->inputs[0], fp);

		fprintf(fp, ")");

	}

	//ALL OTHER
	else {

		fprintf(fp, "%.1f*%s(",
				chromo->nodes[index - chromo->numInputs]->amplitude,
				chromo->funcSet->functionNames[chromo->nodes[index
						- chromo->numInputs]->function]);

		for (i = 0;
				i < _getChromosomeNodeArity(chromo, index - chromo->numInputs);
				i++) {

			_savePrettyChromosomeRecursive(chromo,
					chromo->nodes[index - chromo->numInputs]->inputs[i], fp);

			if (i
					< _getChromosomeNodeArity(chromo, index - chromo->numInputs)
							- 1)
				fprintf(fp, ", ");
		}

		fprintf(fp, ")");
	}
}

#define MAX_F_VAR	3
void _savePrettyChromosome(struct chromosome *chromo, char const *fileName) {
	int output;
	int i;
	FILE *fp;

	//print to console if filename is null
	fp = NULL == fileName ? stdout : fopen(fileName, "w");

	//document header
	fprintf(fp, "-------------------------------------------\n");

	//for all outputs
	for (output = 0; output < chromo->numOutputs; output++) {

		// function inputs
		if (chromo->numInputs == 0) {
			fprintf(fp, "f()=");
		} else {

			fprintf(fp, "f_%d(x_0", output);

			i = chromo->numInputs > MAX_F_VAR ? chromo->numInputs - 1 : 1;

			for (; i < chromo->numInputs; i++) {
				if (chromo->numInputs > MAX_F_VAR) {
					fprintf(fp, ",...,x_%d", i);
				} else {
					fprintf(fp, ",x_%d", i);
				}
			}

			fprintf(fp, ")=");
		}

		_savePrettyChromosomeRecursive(chromo, chromo->outputNodes[output], fp);
		fprintf(fp, "\n-------------------------------------------\n");
	}

	fprintf(fp, "h(C|x_i) = argmax_y MAX(y_0");

	output = chromo->numInputs > MAX_F_VAR ? chromo->numOutputs - 1 : 1;
	for (; output < chromo->numOutputs; output++) {
		if (chromo->numOutputs > MAX_F_VAR) {
			fprintf(fp, ",...,y_%d", output);
		} else {
			fprintf(fp, ",y_%d", output);
		}
	}

	fprintf(fp, ")\n");
	fprintf(fp, "Fitness:\t%f", chromo->fitness);

	fflush(fp);

	if (NULL != fileName) {
		fclose(fp);
	}

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
