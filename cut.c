/**
 * @file cut.c
 * @author Panayiotis Fotiadis 1031373
 * @brief implements cut.h
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

/**
 * @brief exports a cut wave file
 * 
 * @param files table of files, it uses only the first one.
 * @param numOfFiles number of files in **files
 * @param start start time of trimmed wave
 * @param end  end time of trimmed wave
 */
void cut(char **files, int numOfFiles, int start, int end){
    int i;
    for(i=0;i<numOfFiles;i++){
        WAVE *origWave = (WAVE*) malloc(sizeof(WAVE));
        WAVE *cutWave = (WAVE*) malloc(sizeof(WAVE));
        initializeFromFile(origWave,files[i]);
        initializeFromFile(cutWave,files[i]);
        free(cutWave->dataChunk->data);

        int startChunk= start*origWave->fmtChunk->byteRate;
        int endChunk= end*origWave->fmtChunk->byteRate;

        cutWave->dataChunk->data = (byte *)malloc( (origWave->dataChunk->subchunk2Size-(endChunk-startChunk)) * sizeof(byte));
        cutWave->dataChunk->subchunk2Size = origWave->dataChunk->subchunk2Size-(endChunk-startChunk);
        cutWave->riffChunk->chunkSize = origWave->riffChunk->chunkSize - origWave->dataChunk->subchunk2Size + cutWave->dataChunk->subchunk2Size;
        /**
         * @brief copy data from original wave to the cut wave from begin until startChunk and from endChunk until the end
         */
        memcpy(&cutWave->dataChunk->data[0], &origWave->dataChunk->data[0], startChunk);
        memcpy(&cutWave->dataChunk->data[startChunk], &origWave->dataChunk->data[endChunk], origWave->dataChunk->subchunk2Size-endChunk);


        /**
         * @brief export cutted to file -> cut-<filename>
         */
        exportWave(files[i],cutWave,"cut-");
        
        deallocWave(cutWave);
        free(cutWave);
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