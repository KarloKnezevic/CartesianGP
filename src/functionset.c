/*
 * functionset.c
 *
 *  Created on: 14. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "functionset.h"

#include <stdio.h>
#include <string.h>
#include "parameters.h"

void _copyFunctionSet(struct functionSet *funcSetDest,
		struct functionSet *funcSetSrc) {
	int i;

	funcSetDest->numFunctions = funcSetSrc->numFunctions;

	for (i = 0; i < funcSetDest->numFunctions; i++) {
		strncpy(funcSetDest->functionNames[i], funcSetSrc->functionNames[i],
		FUNCTIONNAMELENGTH);
		funcSetDest->functions[i] = funcSetSrc->functions[i];
		funcSetDest->maxNumInputs[i] = funcSetSrc->maxNumInputs[i];
	}
}

void _printFunctionSet(struct parameters *params) {
	int i;

	printf("Function Set:");

	for (i = 0; i < params->funcSet->numFunctions; i++) {
		printf(" %s", params->funcSet->functionNames[i]);
	}

	printf(" (%d)\n", params->funcSet->numFunctions);
}
