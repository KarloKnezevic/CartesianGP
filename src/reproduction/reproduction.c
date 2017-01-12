/*
 * reproduction.c

 *
 *  Created on: 15. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "reproduction.h"
#include "../util.h"
#include <stdlib.h>
#include <string.h>

void mutateRandomParent(struct parameters *params, struct chromosome **parents,
		struct chromosome **children, int numParents, int numChildren) {
	int i;

	//for each child
	for (i = 0; i < numChildren; i++) {
		_copyChromosome(children[i], parents[_randInt(numParents)]);

		_mutateChromosome(params, children[i]);
	}

}

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setCustomReproductionScheme(struct parameters *params,
		void (*reproductionScheme)(struct parameters *params,
				struct chromosome **parents, struct chromosome **children,
				int numParents, int numChildren),
		char const *reproductionSchemeName) {
	if (reproductionScheme == NULL) {
		params->reproductionScheme = mutateRandomParent;
		strncpy(params->reproductionSchemeName, "mutateRandomParent",
		REPRODUCTIONSCHEMENAMELENGTH);
	} else {
		params->reproductionScheme = reproductionScheme;
		strncpy(params->reproductionSchemeName, reproductionSchemeName,
		REPRODUCTIONSCHEMENAMELENGTH);
	}
}
