/*
 * memory.c
 *
 *  Created on: 11. sij 2017.
 *      Author: Karlo Knezevic
 *		  Mail: karlo.knezevic@fer.hr
 */

#include "memory.h"

static int objectCounter = 0;

void* my_malloc(size_t size, const char *file, int line, const char *func) {
	void *p = malloc(size);
	objectCounter++;
	printf("%d) Allocated = %s, %i, %s, %p[%d]\n", objectCounter, file, line,
			func, p, size);

	/*Link List functionality goes in here*/

	return p;
}

void my_free(void *obj, const char *file, int line, const char *func) {
	objectCounter--;

	printf("%d) Dealocated = %s, %i, %s, %p[%d]\n", objectCounter, file, line,
			func, obj, sizeof(obj));

	free(obj);
}
