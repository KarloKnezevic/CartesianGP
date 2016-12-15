/*
 * dataset.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "dataset.h"

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
