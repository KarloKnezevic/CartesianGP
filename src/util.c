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
#include <math.h>
#include "constants/constants.h"

//-----------------------------------------------------------------
//                            RANDOM
//-----------------------------------------------------------------

double _randDecimal(void) {
	return (double) rand() / (double) RAND_MAX;
}

int _randInt(int n) {
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

//-----------------------------------------------------------------
//                            COMPARE
//-----------------------------------------------------------------

int _cmpInt(const void * a, const void * b) {
	return *(int *) a - *(int *) b;
}

int _cmpDouble(const void * a, const void * b) {
	return *(double *) a - *(double *) b;
}

//-----------------------------------------------------------------
//                            SORT
//-----------------------------------------------------------------

void _sortIntArray(int *array, const int length) {
	qsort(array, length, sizeof(int), _cmpInt);
}

void _sortDoubleArray(double *array, const int length) {
	qsort(array, length, sizeof(double), _cmpDouble);
}

//-----------------------------------------------------------------
//                            MEDIAN
//-----------------------------------------------------------------

double _medianInt(const int *anArray, const int length) {
	int i;
	int *copyArray = (int*) malloc(length * sizeof(int));
	double median;

	for (i = 0; i < length; i++) {
		copyArray[i] = anArray[i];
	}

	_sortIntArray(copyArray, length);

	if (length % 2 == 0) {
		median = (copyArray[(length / 2)] + copyArray[(length / 2) - 1]) / 2;
	} else {
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

	_sortDoubleArray(copyArray, length);

	if (length % 2 == 0) {
		median = (copyArray[(length / 2)] + copyArray[(length / 2) - 1]) / 2;
	} else {
		median = copyArray[(length - 1) / 2];
	}

	free(copyArray);
	return median;
}

