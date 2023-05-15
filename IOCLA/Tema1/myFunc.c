#include "myFunc.h"
#include <string.h>
#include <stdlib.h>

power_management_unit* readPMU(FILE *src) {
	power_management_unit *new = (power_management_unit*) calloc(1, sizeof(power_management_unit));
	fread(new, sizeof(power_management_unit), 1, src);
	return new;
}

tire_sensor* readTS(FILE *src) {
	tire_sensor *new = (tire_sensor*) calloc(1, sizeof(tire_sensor));
	fread(new, sizeof(tire_sensor), 1, src);
	return new;
}

void readSensor(FILE *src, sensor* sensor) {
	fread(&sensor->nr_operations, sizeof(int), 1, src);
	int n = sensor->nr_operations;
	sensor->operations_idxs = (int*) calloc(n, sizeof(int));
	fread(sensor->operations_idxs, n * 4, 1, src);
}

void swapSensors(sensor *a, sensor *b) {
	sensor aux;
	aux = (*a);
	*a = *b;
	*b = aux;
}

void sortSensors(sensor *arr, int size) {
	int isSorted = 0, i;
	while(!isSorted) {
		isSorted = 1;
		for(i = 0; i < size - 1; i++)
			if((arr + i)->sensor_type == TIRE && (arr + i + 1)->sensor_type == PMU) {
				swapSensors(arr + i, arr + i + 1);
				isSorted = 0;
			}
	}
}

int charToNum(char str[]) {
	int size = strlen(str);
	int n = 0, i;
	for(i = 0; i < size; i++) n = n * 10 + str[i] - '0';
	return n;
}

int getCommand(char str[]) {
	int result = 0;
	switch (str[0]) {
		case 'p':
			result = 0; //print
			break;
		case 'a':
			result = 1; //analyze
			break;
		case 'c':
			result = 2; //clean
			break;
		case 'e':
			result = 3; //exit
			break;
	}
	return result;
}