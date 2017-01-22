/*
 * BCWStreamImpl.c
 *
 *  Created on: 22. sij 2017.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "BCWStreamImpl.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../functions/functions.h"

struct dataSet *_loadBCWFromStream(char const *file, char const *param) {
	int i;
	struct dataSet *data;
	FILE *fp;
	char *line, *record;
	char buffer[1024];
	int col;

	fp = fopen(file, "r");

	if (fp == NULL) {
		printf("Error: file '%s' cannot be found.\nTerminating.\n", file);
		exit(0);
	}

	data = (struct dataSet*) malloc(sizeof(struct dataSet));

	int training = 0;
	int validation = 0;
	int test = 0;

	int lineNum = -1;
	int readFrom = -1;

	while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL) {

		//config params
		if (lineNum == -1) {

			sscanf(line, "in=%d", &(data->numInputs));

			/**
			 * MT-CGP has one virtual input: vector of all atributes
			 */
			data->numInputs++;

			line = fgets(buffer, sizeof(buffer), fp);

			sscanf(line, "out=%d", &(data->numOutputs));

			line = fgets(buffer, sizeof(buffer), fp);

			sscanf(line, "training_examples=%d", &training);

			line = fgets(buffer, sizeof(buffer), fp);

			sscanf(line, "validation_examples=%d", &validation);

			line = fgets(buffer, sizeof(buffer), fp);

			sscanf(line, "test_examples=%d", &test);

			if (strncmp(param, "train", FUNCTIONNAMELENGTH) == 0) {
				data->numSamples = training;
				readFrom = 0;
			} else if (strncmp(param, "test", FUNCTIONNAMELENGTH) == 0) {
				data->numSamples = test;
				readFrom = training;
			} else {
				printf(
						"Error: Parameter '%s' is not known data was not loaded.\n",
						param);
				exit(-1);
			}

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

			//skip some data
			if (lineNum < readFrom) {
				lineNum++;
				continue;
			}

			//first value
			record = strtok(line, " ,\n");
			col = -1;

			//until the end of line
			int class = -1;
			struct matrix *attributeVector = _initialiseMatrix(1,
					data->numInputs - 1);
			while (record != NULL) {
				if (-1 == col) {
					//ignore ID
				} else if (col < data->numInputs - 1) {
					data->inputData[lineNum - readFrom][col] =
							_initialiseMatrixFromScalar(atof(record));

					attributeVector->data[0][col] = atof(record);

					//add vector
					if (col == data->numInputs - 2) {
						//++col
						data->inputData[lineNum - readFrom][++col] =
								attributeVector;
					}

				} else {
					//2 or 4
					class = atoi(record);
					break;
				}

				record = strtok(NULL, " ,\n");
				col++;
			}

			if (class != 0) {
				for (int i = 0; i < data->numOutputs; i++) {
					data->outputData[lineNum - readFrom][i] =
							(class / 2 - 1) == i ? 1 : 0;
				}
			}
		}

		if (lineNum - readFrom == data->numSamples - 1) {
			break;
		}

		lineNum++;
	}

	fclose(fp);

	return data;
}
