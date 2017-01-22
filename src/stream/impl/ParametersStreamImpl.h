/*
 * ParametersStreamImpl.h
 *
 *  Created on: 22. sij 2017.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef PARAMETERSSTREAMIMPL_H_
#define PARAMETERSSTREAMIMPL_H_

#include "../../dataset.h"
#include "../../parameters.h"

#define PARSER_METHOD_LENGTH 20

void _loadParametersFromStream(struct parameters *params, char const *file,
		struct dataSet **trainingData, struct dataSet **testingData);


#endif /* PARAMETERSSTREAMIMPL_H_ */
