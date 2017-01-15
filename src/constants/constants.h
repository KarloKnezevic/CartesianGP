/*
 * constants.h
 *
 *  Created on: 15. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define EPSILON 1e-10

//-----------------------------------------------------------------
//                         ALGORITHM SETUP
//-----------------------------------------------------------------
#define NUM_INPUT						1
#define NUM_OUTPUT						1
#define NUM_NODES						10
#define NODE_ARITY						2
#define NUM_SAMPLES						5


//-----------------------------------------------------------------
//                       FUNCTION SET SIZE
//-----------------------------------------------------------------

#define FUNCTIONSETSIZE					50

//-----------------------------------------------------------------
//                         STRING LENGTH
//-----------------------------------------------------------------

#define FUNCTIONNAMELENGTH				11
#define FITNESSFUNCTIONNAMELENGTH 		21
#define MUTATIONTYPENAMELENGTH 			21
#define SELECTIONSCHEMENAMELENGTH 		21
#define REPRODUCTIONSCHEMENAMELENGTH 	21

//-----------------------------------------------------------------
//                             CGA
//-----------------------------------------------------------------

#define MU								1
#define LAMBDA							4
#define EVOLUTIONARYSTRATEGY			'+'
#define MUTATIONRATE					0.1
#define RECCURENTCONNECTIONPROBABILITY	0.00
#define CONNECTIONWEIGHTRANGE			0
#define AMPLITUDERANGE					2	//if 0, 1 is set
#define SHORTCUTCONNECTIONS				0
#define TARGETFITNESS					0
#define POPULATIONSIZE					20
#define MAXGEN							1000

//-----------------------------------------------------------------
//                             PRINT
//-----------------------------------------------------------------

#define UPDATEFREQUENCY					1

#endif /* CONSTANTS_H_ */
