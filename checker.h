#ifndef CEHCKER
#define CHECKER
#include "wave.h"
#include <stdbool.h>

bool checkOption(char *argv[]);
bool checkFileFormat(char *fileName);
char **getValidFiles(char *argv[], int *numOfValidFiles);
bool checkTimings(char* fileName, int start, int end);
#endif