/* NENCIU George-Robert - 313CC */
#ifndef ERRORFUNCS_H_
#define ERRORFUNCS_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sendErrorOfFileNull(const char *name, const  char *type, const char *funcName);
void sendErrorOfNull(const char *name, const  char *type, const char *funcName);

#endif