/*
 * selection.h
 *
 *  Created on: 15. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef SELECTION_H_
#define SELECTION_H_

#include "../parameters.h"
#include "../chromosome.h"

void selectFittest(struct parameters *params, struct chromosome **parents,
		struct chromosome **candidateChromos, int numParents,
		int numCandidateChromos);

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setCustomSelectionScheme(struct parameters *params,
		void (*selectionScheme)(struct parameters *params,
				struct chromosome **parents,
				struct chromosome **candidateChromos, int numParents,
				int numCandidateChromos), char const *selectionSchemeName);

#endif /* SELECTION_H_ */
