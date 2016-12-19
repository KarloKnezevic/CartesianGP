/*
 * lialg.h
 *
 *  Created on: 19. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef LIALG_H_
#define LIALG_H_

struct matrix {
	int rows;
	int cols;

	double **data;
};

//-----------------------------------------------------------------
//                          CONSTRUCTOR
//-----------------------------------------------------------------

struct matrix *_initialiseMatrixFromScalar(double scalar);

struct matrix *_initialiseVectorFromArray(int dim, double *array);

struct matrix *_initialiseMatrix(int rows, int cols);

struct matrix *_initialiseMatrixFromArray(int rows, int cols, double *array);

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printMatrix(struct matrix *m);





#endif /* LIALG_H_ */
