#include "list.h"

void list(char **files, int numOfFiles){
    int i;
    printf("\n");
    for(i=0; i< numOfFiles;i++){
        WAVE *tempWave=malloc(sizeof(WAVE));
        initializeFromFile(tempWave,files[i]);
        displayInfo(tempWave);
        if(i<numOfFiles-1)
        printf("\n*********************************************\n");
    }
    
    
}

void displayInfo(WAVE *wave){
    printf("RIFF_CHUNK_HEADER\n");
    printf("=================\n");
    printf("chunkID: %.4s\n",wave->riffChunk->chunkId);
    printf("chunkSize: %d\n",(int) wave->riffChunk->chunkSize);
    printf("format: %.4s\n",wave->riffChunk->format);

    printf("\nFMT_SUBCHUNK_HEADER\n");
    printf("===================\n");
    printf("subChunk1ID: %s\n",wave->fmtChunk->subchunk1Id);
    printf("subChunk1Size: %d\n",(int) wave->fmtChunk->subchunk1Size);
    printf("audioFormat: %d\n",(int) wave->fmtChunk->audioFormat);
    printf("numChannels: %d\n",(int) wave->fmtChunk->numChannels);
    printf("sampleRate: %d\n",(int) wave->fmtChunk->sampleRate);
    printf("byteRate: %d\n",(int) wave->fmtChunk->byteRate);
    printf("blockAlign: %d\n",(int) wave->fmtChunk->blockAlign);
    printf("bitsPerSample: %d\n",(int) wave->fmtChunk->bitsPerSample);

    printf("\nDATA_SUBCHUNK_HEADER\n");
    printf("====================\n");
    printf("subChunk2ID: %.4s\n",wave->dataChunk->subchunk2Id);
    printf("subChunk2Size: %d\n",(int) wave->dataChunk->subchunk2Size);
}