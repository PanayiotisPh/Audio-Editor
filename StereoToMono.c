#include "StereoToMono.h"

void stereoToMono(char **inputFiles, int numOfFiles){
    
    WAVE *wave=NULL;
    WAVE *monoWave = NULL;

    int i,j;
    int insertCounter = 0;

    for(j=0;j<numOfFiles;j++){  

        wave=(WAVE*)malloc(sizeof(WAVE));
        monoWave = (WAVE*) malloc(sizeof(WAVE));

        initializeFromFile(wave,inputFiles[j]);

        initializeFromFile(monoWave,inputFiles[j]);
        if(wave->fmtChunk->numChannels == 1){
            printf("%s has MONO sound. Cannot convert\n", inputFiles[j] );
            continue;
        }

        convertToMono(monoWave);

        for (i=0;i<wave->dataChunk->subchunk2Size; i=i+ (wave->fmtChunk->bitsPerSample)/4){
            memcpy(&monoWave->dataChunk->data[insertCounter], &wave->dataChunk->data[i], wave->fmtChunk->bitsPerSample/8);
            insertCounter = insertCounter+wave->fmtChunk->bitsPerSample/8;
        }
        exportWave(inputFiles[j], monoWave, "mono-");

        insertCounter = 0;
        deallocWave(wave);
        deallocWave(monoWave);
        wave = NULL;
        monoWave =NULL;
    }
}



void convertToMono(WAVE *wave){
    int originalChannels = wave->fmtChunk->numChannels;
    wave->riffChunk->chunkSize = wave->riffChunk->chunkSize/2;

    wave->fmtChunk->numChannels = (word)1;                                      
    wave->fmtChunk->byteRate = wave->fmtChunk->byteRate/2;
    wave->fmtChunk->blockAlign = wave->fmtChunk->blockAlign/2;

    int originalWaveSample = (wave->dataChunk->subchunk2Size) / (originalChannels * (wave->fmtChunk->bitsPerSample / 8));
    wave->dataChunk->subchunk2Size = (originalWaveSample) * (wave->fmtChunk->bitsPerSample / 8);
    wave->dataChunk->data = (byte *)malloc(wave->dataChunk->subchunk2Size * sizeof(byte));
}

#ifndef DEBUGGING
#ifdef DEBUGMONO
#define DEBUGGING
int main(int argc, char *argv[]){
    stereoToMono(argv[1]);
    return 0;
}
#endif
#endif