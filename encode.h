#ifndef ENCODE
#define ENCODE
#include "wave.h"

void encode(char *waveFile, char *textFile);
int getBit(char *m, int n);
int *createPermutationFunction(int N, unsigned int systemkey);


#endif