#include "mix.h"

void mixWaves(char **inputFiles, int numOfFiles){
    WAVE *wave1=NULL;
    WAVE *wave2 = NULL;
    WAVE *mixWaves = NULL;

    int i;
    int insertCounter = 0;
    if(numOfFiles != 2){
        printf("Can not make a mix with %d waves. Import 2 files\n", numOfFiles);
        return;
    }

    wave1=(WAVE*)malloc(sizeof(WAVE));
    wave2 = (WAVE*) malloc(sizeof(WAVE));
    mixWaves =(WAVE*)malloc(sizeof(WAVE));

    initializeFromFile(wave1,inputFiles[0]);
    initializeFromFile(wave2,inputFiles[1]);

    if(wave1->fmtChunk->numChannels != 1 || wave2->fmtChunk->numChannels != 1){
        printf("Waves must be Stereo\n");
        deallocWave(wave1);
        deallocWave(wave2);
        goto Free;
    }
    if(wave1->fmtChunk->bitsPerSample != wave2->fmtChunk->bitsPerSample){
        printf("Waves must have the same BitsPerSample\n");
        deallocWave(wave1);
        deallocWave(wave2);
        goto Free;
    }
    createMixWave(wave2, inputFiles[0]);

    int smallerChunkSize;

    if(wave1->dataChunk->subchunk2Size < wave2->dataChunk->subchunk2Size){
        smallerChunkSize = wave1->dataChunk->subchunk2Size;
    }
    else{
        smallerChunkSize = wave2->dataChunk->subchunk2Size;
    }

    bool switchChannel = true;

    for (i=0;i<smallerChunkSize; i=i+ (wave1->fmtChunk->bitsPerSample)/8){
        if(switchChannel){
            memcpy(&mixWaves->dataChunk->data[insertCounter], &wave2->dataChunk->data[2*i-1], wave2->fmtChunk->bitsPerSample/8);
            insertCounter = insertCounter+wave1->fmtChunk->bitsPerSample/8;
            switchChannel = false;
            continue;
        }
        else if(!switchChannel){
            memcpy(&mixWaves->dataChunk->data[insertCounter], &wave1->dataChunk->data[2*i], wave1->fmtChunk->bitsPerSample/8);
            insertCounter = insertCounter+wave1->fmtChunk->bitsPerSample/8;
            switchChannel = true;
            continue;
        }
    }
    //exportwave1(inputFiles[j], wave2, "mono-");
    Free:
    insertCounter = 0;
    deallocWave(wave1);
    deallocWave(wave2);
    wave1 = NULL;
    wave2 =NULL;
}


void createMixWave(WAVE *mixWave, char *inputFile){
    initializeFromFile(mixWave, inputFile);

    int originalWaveSample = (mixWave->dataChunk->subchunk2Size) / (mixWave->fmtChunk->numChannels * (mixWave->fmtChunk->bitsPerSample / 8));
    mixWave->dataChunk->subchunk2Size = (originalWaveSample) * (mixWave->fmtChunk->bitsPerSample / 8);
    free(mixWave->dataChunk->data);
    mixWave->dataChunk->data = (byte *)malloc(mixWave->dataChunk->subchunk2Size * sizeof(byte));
}