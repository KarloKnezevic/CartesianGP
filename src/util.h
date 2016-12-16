/*
 * util.h
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef UTIL_H_
#define UTIL_H_

//-----------------------------------------------------------------
//                            RANDOM
//-----------------------------------------------------------------

double _randDecimal(void);

int _randInt(int n);

//-----------------------------------------------------------------
//                            COMPARE
//-----------------------------------------------------------------

int _cmpInt(const void * a, const void * b);

int _cmpDouble(const void * a, const void * b);

//-----------------------------------------------------------------
//                            SORT
//-----------------------------------------------------------------

void _sortIntArray(int *array, const int length);

void _sortDoubleArray(double *array, const int length);

//-----------------------------------------------------------------
//                            MEDIAN
//-----------------------------------------------------------------

double _medianInt(const int *anArray, const int length);

double _medianDouble(const double *anArray, const int length);

#endif /* UTIL_H_ */
