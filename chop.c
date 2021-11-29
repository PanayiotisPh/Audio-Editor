/**
 * @file chop.c
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief implements chop.h
 * @version 0.1
 * @date 2021-11-29
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details in the COPYING file.
 *  
 * See license in COPYING file.
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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




#ifndef DEBUGGING
#ifdef DEBUGCHOP
#define DEBUGGING

int main(int argc, char *argv[]){
    //ADD CODE HERE
}

#endif
#endif