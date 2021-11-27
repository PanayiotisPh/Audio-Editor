#include "chop.h"

void chop(char **files, int numOfFiles, int start, int end){
    int i;
    for(i=0;i<numOfFiles;i++){
        WAVE *origWave = (WAVE*) malloc(sizeof(WAVE));
        WAVE *chopWave = (WAVE*) malloc(sizeof(WAVE));
        initializeFromFile(origWave,files[i]);
        initializeFromFile(chopWave,files[i]);
        int startChunk= start*origWave->fmtChunk->byteRate;
        int endChunk= end*origWave->fmtChunk->byteRate;
        int chunkPointer;
        for(chunkPointer=startChunk ; chunkPointer<endChunk ; chunkPointer+= origWave->fmtChunk->sampleRate/8  ){
            
        }

        


        deallocWave(origWave);
        free(origWave);

    }

}