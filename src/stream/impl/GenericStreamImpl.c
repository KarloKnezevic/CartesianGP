/*
 * GenericStreamImpl.c
 *
 *  Created on: 22. sij 2017.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "GenericStreamImpl.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct dataSet *_loadGenericFromStream(char const *file) {
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
