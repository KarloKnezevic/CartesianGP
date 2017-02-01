/*
 * ParametersStreamImpl.c
 *
 *  Created on: 22. sij 2017.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "ParametersStreamImpl.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../stream.h"
#include "../../mutation/mutation.h"

#define SPECIAL_CHAR '#'
#define PARAM_LENGTH 30

void _loadParametersFromStream(struct parameters *params, char const *file,
		struct dataSet **trainingData, struct dataSet **testingData) {

	int i;
	FILE *fp;
	char *line, *record;
	char buffer[1024];

	fp = fopen(file, "r");

	if (fp == NULL) {
		LOG(params, "Error: file '%s' cannot be found.\nTerminating.\n", file);
		exit(0);
	}

	char parsermethod[PARSER_METHOD_LENGTH];

	while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL) {
		//if space
		for (i = 0; line[i] && isspace(line[i]); i++)
			;

		if (line[i] == SPECIAL_CHAR) {
			continue;
		}

		record = strtok(line, " =\n");

		while (record != NULL) {

			//method
			if (strcmp(record, "parsermethod") == 0) {
				record = strtok(NULL, " =\n");
				strncpy(parsermethod, record, PARSER_METHOD_LENGTH);
			}

			//training
			if (strcmp(record, "training") == 0) {
				record = strtok(NULL, " =\n");
				*trainingData = _loadGenericMethodDataSetFromFile(parsermethod,
						record, "train");
			}

			//testing
			if (strcmp(record, "testing") == 0) {
				record = strtok(NULL, " =\n");
				*testingData = _loadGenericMethodDataSetFromFile(parsermethod,
						record, "test");
			}

			//inputs
			if (strcmp(record, "inputs") == 0) {
				record = strtok(NULL, " =\n");
				_setNumInputs(params, atoi(record));
			}

			//outputs
			if (strcmp(record, "outputs") == 0) {
				record = strtok(NULL, " =\n");
				_setNumOutputs(params, atoi(record));
			}

			//nodes
			if (strcmp(record, "nodes") == 0) {
				record = strtok(NULL, " =\n");
				_setNumNodes(params, atoi(record));
			}

			//arity
			if (strcmp(record, "arity") == 0) {
				record = strtok(NULL, " =\n");
				_setArity(params, atoi(record));
			}

			//shortcutconnections
			if (strcmp(record, "shortcutconnections") == 0) {
				record = strtok(NULL, " =\n");
				_setShortcutConnections(params, atoi(record));
			}

			//functions
			if (strcmp(record, "functions") == 0) {
				record = strtok(NULL, " =\n");
				_addNodeFunction(params, record);
			}

			//mu
			if (strcmp(record, "mu") == 0) {
				record = strtok(NULL, " =\n");
				_setMu(params, atoi(record));
			}

			//lambda
			if (strcmp(record, "lambda") == 0) {
				record = strtok(NULL, " =\n");
				_setLambda(params, atoi(record));
			}

			//strategy
			if (strcmp(record, "strategy") == 0) {
				record = strtok(NULL, " =\n");
				_setEvolutionaryStrategy(params, record[0]);
			}

			//mutationrate
			if (strcmp(record, "mutationrate") == 0) {
				record = strtok(NULL, " =\n");
				_setMutationRate(params, atof(record));
			}

			//mutationtype
			if (strcmp(record, "mutationtype") == 0) {
				record = strtok(NULL, " =\n");
				_setMutationType(params, record);
			}

			//amplitude
			if (strcmp(record, "amplitude") == 0) {
				record = strtok(NULL, " =\n");
				_setAmplitudeRange(params, atof(record));
			}

			//runs
			if (strcmp(record, "runs") == 0) {
				record = strtok(NULL, " =\n");
				_setNumRuns(params, atoi(record));
			}

			//generations
			if (strcmp(record, "generations") == 0) {
				record = strtok(NULL, " =\n");
				_setNumGenerations(params, atoi(record));
			}

			//stagnation
			if (strcmp(record, "stagnation") == 0) {
				record = strtok(NULL, " =\n");
				_setNumGenStagnation(params, atoi(record));
			}

			//regularization
			if (strcmp(record, "regularization") == 0) {
				record = strtok(NULL, " =\n");
				_setL1Regularization(params, atoi(record));
			}

			//update frequency
			if (strcmp(record, "updatefrequency") == 0) {
				record = strtok(NULL, " =\n");
				_setUpdateFrequency(params, atoi(record));
			}

			record = strtok(NULL, " =\n");
		}

	}

	fclose(fp);
}
