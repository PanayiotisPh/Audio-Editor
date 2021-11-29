/**
 * @file reverse.c
 * @author Panayiotis Fotiadis 1031373
 * @brief   reverse the data of the wave
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
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
 */
#include "reverse.h"

void reverseWave(char **inputFiles, int numOfFiles){
    int i;
    WAVE *wave = NULL;
    for (i = 0; i < numOfFiles; i++){       //loop throught each file
        wave = (WAVE*)malloc(sizeof(WAVE));
        initializeFromFile(wave,inputFiles[i]);     //copy the file data to wave
        if(wave->fmtChunk->numChannels == 1){   //if wave is mono
            reverseMono(wave, inputFiles[i]);
        }
        else{
            reverseStereo(wave, inputFiles[i]); //if wave is stereo
        }
        deallocWave(wave);
        free(wave);
    }
    

}
void reverseStereo(WAVE *wave, char *inputFile){
    WAVE *reverseWave =NULL;
    reverseWave = (WAVE*)malloc(sizeof(WAVE));      //create new wave to store the reversed data
    createReverseWave(reverseWave, inputFile);      //copy the data from file and free the data segment
    int i;
    int waveCounter = 0;    //used as index for the data of the original wave

    for(i=wave->dataChunk->subchunk2Size- (wave->fmtChunk->bitsPerSample/4) ; i>=0; i = i-(wave->fmtChunk->bitsPerSample/4)){   //loop from end to begin from sample to sample
        memcpy(&reverseWave->dataChunk->data[i], &wave->dataChunk->data[waveCounter], wave->fmtChunk->bitsPerSample/4); //copy the data from origianl to reverseWave
        waveCounter = waveCounter + wave->fmtChunk->bitsPerSample/4;    //jump to next byte
    }
    exportWave(inputFile, reverseWave,"reverse-");  //export Wave
    deallocWave(reverseWave);
    free(reverseWave);
    reverseWave =NULL;
}

void reverseMono(WAVE *wave, char *inputFile){
    WAVE *reverseWave =NULL;
    reverseWave = (WAVE*)malloc(sizeof(WAVE));
    createReverseWave(reverseWave, inputFile);
    int i;
    int waveCounter = 0;
    printf("%d\t%d\n", wave->dataChunk->subchunk2Size- (wave->fmtChunk->bitsPerSample/8), waveCounter);

    for(i=wave->dataChunk->subchunk2Size- (wave->fmtChunk->bitsPerSample/8) ; i>=0; i = i-(wave->fmtChunk->bitsPerSample/8)){   //loop from end to begin moving 2 samples(left and right) each time
        memcpy(&reverseWave->dataChunk->data[i], &wave->dataChunk->data[waveCounter], wave->fmtChunk->bitsPerSample/8); //copy both channels from original wave to reverse wave
        waveCounter = waveCounter + wave->fmtChunk->bitsPerSample/8;    //move to next 2 samples
    }
    exportWave(inputFile, reverseWave,"reverse-");  //export wave
    deallocWave(reverseWave);
    free(reverseWave);
    reverseWave =NULL;
}

void createReverseWave(WAVE *reverseWave, char *inputFile){
    initializeFromFile(reverseWave, inputFile); //copy the data fro file
    free(reverseWave->dataChunk->data); //free the data
    reverseWave->dataChunk->data = (byte *)malloc(reverseWave->dataChunk->subchunk2Size * sizeof(byte));    //assign them new free space
}


#ifndef DEBUGGING
#ifdef DEBUGREVERSE
#define DEBUGGING

int main(int argc, char *argv[]){
    //ADD CODE HERE
}

#endif
#endif