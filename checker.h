#ifndef CEHCKER
#define CHECKER
#include "wave.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

bool checkOption(char *argv[]);
bool isValidWaveFile(char *fileName);
char **getValidFiles(char *argv[], int *numOfValidFiles);
bool checkTimings(char* fileName, int start, int end);
bool isTextFile(char *fileName);
#endif