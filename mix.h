#ifndef MIX
#define MIX
#include "wave.h"

void mixWaves(char **inputFiles, int numOfFiles);
void createNewWave(char *input, WAVE *monoWave);
void initializeMixWave(WAVE *mixWave);



#endif