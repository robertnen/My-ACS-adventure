#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myFunc.h"
#include "sensorOperations.h"

int main(int argc, char const *argv[]) {

	FILE *src = fopen(argv[1], "rb");
	int n, i, type;

	fread(&n, sizeof(int), 1, src);
	sensor *sensors = (sensor*) calloc(n, sizeof(sensor));

	for(i = 0; i < n; i++) {
		fread(&type, sizeof(int), 1, src);
		(sensors + i)->sensor_type = type;
		if(type) { //PMU
			power_management_unit *pmu = readPMU(src);
			(sensors + i)->sensor_data = (void*) pmu;
		} else { //TS
			tire_sensor *ts = readTS(src);
			(sensors + i)->sensor_data = (void*) ts;
		}
		readSensor(src, sensors + i);
	}

	fclose(src); //am citit tot ce era in fisier
	sortSensors(sensors, n);

	char inputCommand[100];
	int pos;
	i = 0;
	while(fgets(inputCommand, 100, stdin)) { //citirea + executarea operatiilor
		inputCommand[strlen(inputCommand) - 1] = '\0';
		pos = getCommand(inputCommand);
		switch(pos) {
			case 0:	//operatia print care are 5 caractere + space
				print(sensors, n, charToNum(inputCommand + 6));
				break;
			case 1:	//operatia analyze care are 7 caractere + space
				analyze(sensors, n, charToNum(inputCommand + 8));
				break;
			case 2: //operatia clean
				sensors = clean(sensors, &n);
				break;
			case 3: //operatia exit
				exitS(sensors, n);
		}
	}

	for(i = 0; i < n; i++) { //eliberarea memoriei daca nu se apeleaza exit
		free((sensors + i)->operations_idxs);
		free((sensors + i)->sensor_data);
	}
	free(sensors);
	return 0;
}