#include "sensorOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myFunc.h"

void get_operations(void **operations);

void print(sensor *arr, int size, int pos) {
	power_management_unit *p;
	tire_sensor *t;
	if(pos > -1 && pos < size) {
		if((arr + pos)->sensor_type == PMU) {
			p = (power_management_unit*)((arr + pos)->sensor_data);
			printf("Power Management Unit\n");
			printf("Voltage: %.2f\n", p->voltage);
			printf("Current: %.2f\n", p->current);
			printf("Power Consumption: %.2f\n", p->power_consumption);
			printf("Energy Regen: %d%%\n", p->energy_regen);
			printf("Energy Storage: %d%%\n", p->energy_storage);
		} else {
			t = (tire_sensor*)((arr + pos)->sensor_data);
			printf("Tire Sensor\n");
			printf("Pressure: %.2f\n", t->pressure);
			printf("Temperature: %.2f\n", t->temperature);
			printf("Wear Level: %d%%\n", t->wear_level);
			printf("Performance Score: ");
			if(t->performace_score) printf("%d\n", t->performace_score);
			else printf("Not Calculated\n");
		}
	} else printf("Index not in range!\n");
}

void analyze(sensor *arr, int size, int pos) {
	void *getFunc[8];
	get_operations(getFunc);
	void (*operations[8])();

	int i, n = (arr + pos)->nr_operations;
	for(i = 0; i < 8; i++) operations[i] = getFunc[i];

	if(pos > -1 && pos < size) {
		for(i = 0; i < n; i++)
			operations[(arr + pos)->operations_idxs[i]]((arr + pos)->sensor_data);
	} else printf("Index not in range!\n");
}

sensor* clean(sensor *arr, int *size) {
	int i = 0, j, counter, isValid;
	power_management_unit *p;
	tire_sensor *t;
	while(i < (*size)) {
		counter = 0; //nr de conditii indeplinite
		isValid = 1;
		if((arr + i)->sensor_type == PMU) {
			p = (power_management_unit*)((arr + i)->sensor_data);
			if(p->voltage >= 10 && p->voltage <= 20) counter++;
			if(p->current >= -100 && p->current <= 100) counter++;
			if(p->power_consumption >= 0 && p->power_consumption <= 1000) counter++;
			if(p->energy_regen >= 0 && p->energy_regen <= 100) counter++;
			if(p->energy_storage >= 0 && p->energy_storage <= 100) counter++;

			if(counter != 5) isValid = 0;

		} else {
			t = (tire_sensor*)((arr + i)->sensor_data);
			if(t->pressure >= 19 && t->pressure <= 28) counter++;
			if(t->temperature >= 0 && t->temperature <= 120) counter++;
			if(t->wear_level >= 0 && t->wear_level <= 100) counter++;

			if(counter != 3) isValid = 0;
		}
		if(!isValid) {
			free((arr + i)->sensor_data);
			free((arr + i)->operations_idxs);
			(*size)--;
			for(j = i; j < *size; j++) //duc in capat ce e invalid si scap de el
				swapSensors((arr + j), (arr + j + 1));
			arr = (sensor*) realloc(arr, (*size) * sizeof(sensor)); // de ce trb realocare??
		} else i++;
	}
	return arr;
}

void exitS(sensor *arr, int size) {

	int i;
	for(i = 0; i < size; i++) {
		free((arr + i)->operations_idxs);
		free((arr + i)->sensor_data);
	}
	free(arr);
	exit(1);
}
