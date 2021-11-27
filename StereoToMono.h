#ifndef STEREOTOMONO
#define STEREOTOMONO
#include "wave.h"

void stereoToMono(char **inputFiles, int numOfFiles);
void createNewWave(char *input, WAVE *monoWave);
void initializeMonoWave(WAVE *monoWave);



#endif