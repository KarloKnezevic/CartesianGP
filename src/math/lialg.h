/*
 * lialg.h
 *
 *  Created on: 19. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef LIALG_H_
#define LIALG_H_

typedef enum {NONE, SCALAR, VECTOR, MATRIX} mtype;

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
//                            SETTER
//-----------------------------------------------------------------

void _setSMatrixData(struct matrix *m, double val);

void _setMatrixData(struct matrix *m, int i, int j, double val);

//-----------------------------------------------------------------
//                            GETTER
//-----------------------------------------------------------------

double _getMatrixAsScalar(struct matrix *m);

//-----------------------------------------------------------------
//                            TOSTRING
//-----------------------------------------------------------------

void _printMatrix(struct matrix *m);

//-----------------------------------------------------------------
//                          DESTRUCT
//-----------------------------------------------------------------

void _freeMatrix(struct matrix *m);

//-----------------------------------------------------------------
//                          MATH
//-----------------------------------------------------------------

double _zerro_div(double a, double b);

struct matrix* _mulWithScalar(struct matrix *m, double scalar);

struct matrix* _sumElements(struct matrix *m1, const double *factors);

struct matrix* _add(struct matrix *m1, struct matrix *m2, const double *factors);

struct matrix* _sub(struct matrix *m1, struct matrix *m2, const double *factors);

struct matrix* _div(struct matrix *m1, struct matrix *m2, const double *factors);

struct matrix* _mul(struct matrix *m1, struct matrix *m2, const double *factors);

struct matrix* _abs(struct matrix *m1, const double *factors);

struct matrix* _sqrt(struct matrix *m1, const double *factors);

struct matrix* _pow(struct matrix *m1, struct matrix *m2, const double *factors);

struct matrix* _powInt(struct matrix *m1, struct matrix *m2, const double *factors);

//-----------------------------------------------------------------
//                          UTILITY
//-----------------------------------------------------------------

mtype _getMatrixType(struct matrix *m);

void _checkMatrixForNaN(struct matrix *m, double val);

void _checkMatrixForInf(struct matrix *m);

void _copyMatrix(struct matrix *mDest, struct matrix *mSrc);

struct matrix *_copyMatrixOf(struct matrix *m);

#endif /* LIALG_H_ */
