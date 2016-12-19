/*
 * stream.h
 *
 *  Created on: 16. pro 2016.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef STREAM_H_
#define STREAM_H_

#include "../chromosome.h"

//-----------------------------------------------------------------
//                          READERS
//-----------------------------------------------------------------

struct chromosome* _loadChromosomeFromFile(char const *file);

struct dataSet *_loadDataSetFromFile(char const *file);


//-----------------------------------------------------------------
//                          WRITERS
//-----------------------------------------------------------------

void _saveChromosome(struct chromosome *chromo, char const *fileName);

void _saveDataSet(struct dataSet *data, char const *fileName);


#endif /* STREAM_H_ */
