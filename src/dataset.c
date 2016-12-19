/*
 * dataset.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "dataset.h"
#include <stdio.h>
#include <stdlib.h>
#include "stream/stream.h"

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct dataSet *_initialiseDataSetFromArrays(int numInputs, int numOutputs,
		int numSamples, double *inputs, double *outputs) {
	int i, j;
	struct dataSet *data;

	data = (struct dataSet*) malloc(sizeof(struct dataSet));

	data->numInputs = numInputs;
	data->numOutputs = numOutputs;
	data->numSamples = numSamples;

	data->inputData = (double**) malloc(data->numSamples * sizeof(double*));
	data->outputData = (double**) malloc(data->numSamples * sizeof(double*));

	for (i = 0; i < data->numSamples; i++) {

		data->inputData[i] = (double*) malloc(data->numInputs * sizeof(double));
		data->outputData[i] = (double*) malloc(
				data->numOutputs * sizeof(double));

		for (j = 0; j < data->numInputs; j++) {
			data->inputData[i][j] = inputs[(i * data->numInputs) + j];
		}

		for (j = 0; j < data->numOutputs; j++) {
			data->outputData[i][j] = outputs[(i * data->numOutputs) + j];
		}
	}

	return data;
}

struct dataSet *_initialiseDataSetFromFile(char const *file) {
	return _loadDataSetFromFile(file);
}

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printDataSet(struct dataSet *data) {
	int i, j;

	printf("DATA SET\n");
	printf("Inputs: %d, ", data->numInputs);
	printf("Outputs: %d, ", data->numOutputs);
	printf("Samples: %d\n", data->numSamples);

	for (i = 0; i < data->numSamples; i++) {

		for (j = 0; j < data->numInputs; j++) {
			printf("%f ", data->inputData[i][j]);
		}

		printf(" : ");

		for (j = 0; j < data->numOutputs; j++) {
			printf("%f ", data->outputData[i][j]);
		}

		printf("\n");
	}
}

//-----------------------------------------------------------------
//                            GETTERS
//-----------------------------------------------------------------

int _getNumDataSetInputs(struct dataSet *data) {
	return data->numInputs;
}

int _getNumDataSetOutputs(struct dataSet *data) {
	return data->numOutputs;
}

int _getNumDataSetSamples(struct dataSet *data) {
	return data->numSamples;
}

double _getDataSetSampleOutput(struct dataSet *data, int sample, int output) {
	return data->outputData[sample][output];
}

double *_getDataSetSampleInputs(struct dataSet *data, int sample) {
	return data->inputData[sample];
}

double _getDataSetSampleInput(struct dataSet *data, int sample, int input) {
	return data->inputData[sample][input];
}

double *_getDataSetSampleOutputs(struct dataSet *data, int sample) {
	return data->outputData[sample];
}

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeDataSet(struct dataSet *data) {
	int i;

	/* attempt to prevent user double freeing */
	if (data == NULL) {
		printf("Warning: double freeing of dataSet prevented.\n");
		return;
	}

	for (i = 0; i < data->numSamples; i++) {
		free(data->inputData[i]);
		free(data->outputData[i]);
	}

	free(data->inputData);
	free(data->outputData);
	free(data);
}
