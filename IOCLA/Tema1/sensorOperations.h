#ifndef _SENSOROPERATIONS_H_
#define _SENSOROPERATIONS_H_

#include "structs.h"

void print(sensor *arr, int size, int pos);
void analyze(sensor *arr, int size, int pos);
sensor* clean(sensor *arr, int *size);
void exitS(sensor *arr, int size);

#endif // _SENSOROPERATIONS_H_