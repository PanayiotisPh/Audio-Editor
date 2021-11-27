#include "chop.h"

void chop(char **files, int numOfFiles, int start, int end){
    int i;
    for(i=0;i<numOfFiles;i++){
        WAVE *origWave = (WAVE*) malloc(sizeof(WAVE));
        WAVE *chopWave = (WAVE*) malloc(sizeof(WAVE));
        initializeFromFile(origWave,files[i]);
        initializeFromFile(chopWave,files[i]);
        free(chopWave->dataChunk->data);

        int startChunk= start*origWave->fmtChunk->byteRate;
        int endChunk= end*origWave->fmtChunk->byteRate;
        chopWave->dataChunk->data = (byte *)malloc( (endChunk-startChunk) * sizeof(byte));
        chopWave->dataChunk->subchunk2Size= endChunk-startChunk;
        
        // int chunkPointer;
        // for(chunkPointer=startChunk ; chunkPointer<endChunk ; chunkPointer+= origWave->fmtChunk->sampleRate/8  ){
            
        // }
        memcpy(&chopWave->dataChunk->data[0], &origWave->dataChunk->data[startChunk], endChunk-startChunk);

        exportWave(files[i],chopWave,"chopped-");
        
        deallocWave(chopWave);
        free(chopWave);
        deallocWave(origWave);
        free(origWave);

    }

}