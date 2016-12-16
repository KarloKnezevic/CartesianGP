/*
 * dataset.h
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef DATASET_H_
#define DATASET_H_

struct dataSet {
	int numSamples;

	int numInputs;

	int numOutputs;

	double **inputData;

	double **outputData;
};

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct dataSet *_initialiseDataSetFromArrays(
        int numInputs,
        int numOutputs,
        int numSamples,
        double *inputs,
        double *outputs
);

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printDataSet(struct dataSet *data);

//-----------------------------------------------------------------
//                            GETTERS
//-----------------------------------------------------------------

int _getNumDataSetInputs(struct dataSet *data);

int _getNumDataSetOutputs(struct dataSet *data);

int _getNumDataSetSamples(struct dataSet *data);

double _getDataSetSampleOutput(struct dataSet *data, int sample, int output);

double *_getDataSetSampleInputs(struct dataSet *data, int sample);

double _getDataSetSampleInput(struct dataSet *data, int sample, int input);

double *_getDataSetSampleOutputs(struct dataSet *data, int sample);

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeDataSet(struct dataSet *data);

#endif /* DATASET_H_ */
