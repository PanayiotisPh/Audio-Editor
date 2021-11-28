#ifndef REVERSE
#define REVERSE
#include "wave.h"

void reverseWave(char **inputFiles, int numOfFiles);
void reverseStereo(WAVE *wave, char *inputFile);
void reverseMono(WAVE *wave, char *inputFile);
void createReverseWave(WAVE *reverseWave, char *inputFile);

#endif