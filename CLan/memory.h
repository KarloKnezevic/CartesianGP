/*
 * memory.h
 *
 *  Created on: 11. sij 2017.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Example of call
 *
 * #include "../CLan/memory.h"
 * #define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)
 * #define free(X) my_free( X, __FILE__, __LINE__, __FUNCTION__)
 */

void* my_malloc(size_t size, const char *file, int line, const char *func);

void my_free(void *obj, const char *file, int line, const char *func);

#endif /* MEMORY_H_ */
