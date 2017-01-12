/*
 * selection.c
 *
 *  Created on: 15. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "selection.h"

#include <stdlib.h>
#include <string.h>

void selectFittest(struct parameters *params, struct chromosome **parents,
		struct chromosome **candidateChromos, int numParents,
		int numCandidateChromos) {
	int i;

	_sortChromosomeArray(candidateChromos, numCandidateChromos);

	for (i = 0; i < numParents; i++) {
		_copyChromosome(parents[i], candidateChromos[i]);
	}
}

//-----------------------------------------------------------------
//                          FACTORY
//-----------------------------------------------------------------

void _setCustomSelectionScheme(struct parameters *params,
		void (*selectionScheme)(struct parameters *params,
				struct chromosome **parents,
				struct chromosome **candidateChromos, int numParents,
				int numCandidateChromos), char const *selectionSchemeName) {

	if (selectionScheme == NULL) {
		params->selectionScheme = selectFittest;
		strncpy(params->selectionSchemeName, "selectFittest",
		SELECTIONSCHEMENAMELENGTH);
	} else {
		params->selectionScheme = selectionScheme;
		strncpy(params->selectionSchemeName, selectionSchemeName,
		SELECTIONSCHEMENAMELENGTH);
	}
}

