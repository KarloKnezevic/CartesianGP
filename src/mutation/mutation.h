/*
 * mutation.h
 *
 *  Created on: 15. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef MUTATION_H_
#define MUTATION_H_

#include "../parameters.h"
#include "../chromosome.h"

void probabilisticMutation(struct parameters *params, struct chromosome *chromo);

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setMutationType(struct parameters *params, char const *mutationType);

#endif /* MUTATION_H_ */
