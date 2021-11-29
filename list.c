/**
 * @file list.c
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief implements list.h
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

#include "list.h"

/**
 * @brief lists to the display all the headers of the wave files given in the argument line
 * 
 * @param files 
 * @param numOfFiles 
 */
void list(char **files, int numOfFiles){
    int i;
    WAVE *tempWave=malloc(sizeof(WAVE));

    printf("\n");
    for(i=0; i< numOfFiles;i++){
        initializeFromFile(tempWave,files[i]);
        displayInfo(tempWave);
        if(i<numOfFiles-1)
        printf("\n*********************************************\n");
        deallocWave(tempWave);
    }
    free(tempWave);
    
    
}

/**
 * @brief prints header to the screen
 * 
 * @param wave 
 */
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


#ifndef DEBUGGING
#ifdef DEBUGLIST
#define DEBUGGING

int main(int argc, char *argv[]){
    //ADD CODE HERE
}

#endif
#endif