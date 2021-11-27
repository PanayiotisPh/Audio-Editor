#include "chop.h"

void chop(char **files, int numOfFiles, int start, int end){
    int i;
    for(i=0;i<numOfFiles;i++){
        WAVE *origWave = (WAVE*) malloc(sizeof(WAVE));
        WAVE *chopWave = (WAVE*) malloc(sizeof(WAVE));
        initializeFromFile(origWave,files[i]);
        initializeFromFile(chopWave,files[i]);
        free(chopWave->dataChunk->data);
        chopWave->dataChunk->data = (byte *)malloc( (end-start) * sizeof(byte));

        int startChunk= start*origWave->fmtChunk->byteRate;
        int endChunk= end*origWave->fmtChunk->byteRate;
        // int chunkPointer;
        // for(chunkPointer=startChunk ; chunkPointer<endChunk ; chunkPointer+= origWave->fmtChunk->sampleRate/8  ){
            
        // }
        memcpy(chopWave->dataChunk->data,origWave->dataChunk->data[start],end-start);

        exportWave(files[i],chopWave,"chopped-");
        
        deallocWave(chopWave);
        free(chopWave);
        deallocWave(origWave);
        free(origWave);

    }

}