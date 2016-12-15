/*
 * reproduction.h
 *
 *  Created on: 15. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef REPRODUCTION_H_
#define REPRODUCTION_H_

#include "../parameters.h"
#include "../chromosome.h"

void mutateRandomParent(struct parameters *params, struct chromosome **parents,
		struct chromosome **children, int numParents, int numChildren);

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setCustomReproductionScheme(struct parameters *params,
		void (*reproductionScheme)(struct parameters *params,
				struct chromosome **parents, struct chromosome **children,
				int numParents, int numChildren),
		char const *reproductionSchemeName);

#endif /* REPRODUCTION_H_ */
