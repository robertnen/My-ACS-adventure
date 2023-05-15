#ifndef _MYFUNC_H_
#define _MYFUNC_H_

#include "structs.h"
#include <stdio.h>

power_management_unit* readPMU(FILE *src);  //power management unit
tire_sensor* readTS(FILE *src);             //tire sensor
void readSensor(FILE *src, sensor* sensor); //aici se citesc operatiile
void swapSensors(sensor *a, sensor *b);     //pentru sortare
void sortSensors(sensor *arr, int size);    //sortare
int charToNum(char str[]);                  //pentru executia operatiilor
int getCommand(char str[]);                 //pentru a gasi ce operatie e

#endif // _MYFUNC_H_