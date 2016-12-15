/*
 * fitness.h
 *
 *  Created on: 15. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef FITNESS_H_
#define FITNESS_H_

#include "../parameters.h"
#include "../chromosome.h"
#include "../dataset.h"

double supervisedLearning(struct parameters *params, struct chromosome *chromo,
		struct dataSet *data);

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setCustomFitnessFunction(struct parameters *params,
		double (*fitnessFunction)(struct parameters *params,
				struct chromosome *chromo, struct dataSet *data),
		char const *fitnessFunctionName);

#endif /* FITNESS_H_ */
