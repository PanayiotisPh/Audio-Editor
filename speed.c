#include "wave.h"

void changeSpeed(char *fileName, float speedMult){
    WAVE *wave = (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,fileName);
    wave->fmtChunk->sampleRate *= speedMult;
    exportWave(fileName,wave,"speed-");
    deallocWave(wave);
    free(wave);


}