#include "mix.h"

void mixWaves(char **inputFiles, int numOfFiles){
    WAVE *wave1=NULL;
    WAVE *wave2 = NULL;
    WAVE *mixWaves = NULL;

    int i;
    if(numOfFiles != 2){
        printf("Can not make a mix with %d waves. Import 2 files\n", numOfFiles);
        return;
    }

    wave1=(WAVE*)malloc(sizeof(WAVE));
    wave2 = (WAVE*) malloc(sizeof(WAVE));
    mixWaves =(WAVE*)malloc(sizeof(WAVE));

    initializeFromFile(wave1,inputFiles[0]);
    initializeFromFile(wave2,inputFiles[1]);

    if(wave1->fmtChunk->numChannels != 2 || wave2->fmtChunk->numChannels != 2){
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

    int smallerChunkSize;

    if(wave1->dataChunk->subchunk2Size < wave2->dataChunk->subchunk2Size){
        smallerChunkSize = wave1->dataChunk->subchunk2Size;
        createMixWave(mixWaves, inputFiles[0]);

    }
    else{
        smallerChunkSize = wave2->dataChunk->subchunk2Size;
        createMixWave(mixWaves, inputFiles[1]);
    }

    bool switchChannel = true;
    int insertCounterWave1 = wave1->fmtChunk->bitsPerSample/8;
    int insertCounterWave2 = 0;



    for (i=0;i<smallerChunkSize; i=i+ (wave1->fmtChunk->bitsPerSample)/8){
        if(switchChannel){
            memcpy(&mixWaves->dataChunk->data[i], &wave2->dataChunk->data[insertCounterWave2], wave2->fmtChunk->bitsPerSample/8);
            insertCounterWave2 = insertCounterWave2 + wave2->fmtChunk->bitsPerSample/4;
            switchChannel = false;
            continue;
        }
        else if(!switchChannel){
            memcpy(&mixWaves->dataChunk->data[i], &wave1->dataChunk->data[insertCounterWave1], wave1->fmtChunk->bitsPerSample/8);
            insertCounterWave1 = insertCounterWave1 + wave1->fmtChunk->bitsPerSample/4;
            switchChannel = true;
            continue;
        }
    }

    char *outputfile = calloc(strlen(inputFiles[0]) + 6,1);
    strcat(outputfile,"mix-");
    strcat(outputfile,inputFiles[0]);
    strcat(outputfile,"-");
    exportWave(inputFiles[1], mixWaves, outputfile);
    
    Free:
    deallocWave(wave1);
    deallocWave(wave2);
    wave1 = NULL;
    wave2 =NULL;
}


void createMixWave(WAVE *mixWave, char *inputFile){
    initializeFromFile(mixWave, inputFile);
    free(mixWave->dataChunk->data);
    mixWave->dataChunk->data = (byte *)malloc(mixWave->dataChunk->subchunk2Size * sizeof(byte));
}