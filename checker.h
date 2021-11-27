#ifndef CEHCKER
#define CHECKER
#include "wave.h"
#include <stdbool.h>

bool checkOption(char *argv[]);
bool checkFileFormat(char *fileName);
char **getValidFiles(char *argv[], int *numOfValidFiles);

#endif