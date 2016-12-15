/*
 * util.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "util.h"

#include <stdlib.h>
#include <assert.h>

double randDecimal(void) {
	return (double) rand() / (double) RAND_MAX;
}

int randInt(int n) {
	if ((n - 1) == RAND_MAX) {
		return rand();
	} else {
		// truncate skew
		long end = RAND_MAX / n;
		assert(end > 0L);
		end *= n;

		int r;
		while ((r = rand()) >= end)
			;

		return r % n;
	}

}

void sortIntArray(int *array, const int length) {
	//todo
}

double medianInt(const int *anArray, const int length) {

	int i;
	int *copyArray = (int*) malloc(length * sizeof(int));
	double median;

	for (i = 0; i < length; i++) {
		copyArray[i] = anArray[i];
	}

	//todo: sort!
	//sortIntArray(copyArray, length);

	if (length % 2 == 0) {
		median = (copyArray[(length / 2)] + copyArray[(length / 2) - 1]) / 2;
	}

	else {
		median = copyArray[(length - 1) / 2];
	}

	free(copyArray);

	return median;
}

double _medianDouble(const double *anArray, const int length) {

	int i;
	double *copyArray = (double*) malloc(length * sizeof(double));
	double median;

	for (i = 0; i < length; i++) {
		copyArray[i] = anArray[i];
	}

	//todo: sort!
	//sortDoubleArray(copyArray, length);

	if (length % 2 == 0) {
		median = (copyArray[(length / 2)] + copyArray[(length / 2) - 1]) / 2;
	}

	else {
		median = copyArray[(length - 1) / 2];
	}

	free(copyArray);

	return median;
}

