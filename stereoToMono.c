/**
 * @file stereoToMono.h
 * @author Panayiotis Fotiadis 1031373
 * @brief converts a wave from stereo to mono 
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
#include "stereoToMono.h"

void stereoToMono(char **inputFiles, int numOfFiles){
    
    WAVE *wave=NULL;
    WAVE *monoWave = NULL;

    int i,j;
    int insertCounter = 0;  //used as index for origianl wave
   

    for(j=0;j<numOfFiles;j++){  

        wave=(WAVE*)malloc(sizeof(WAVE));
        monoWave = (WAVE*) malloc(sizeof(WAVE));
        initializeFromFile(wave,inputFiles[j]);     //initilize the origianl wave
        initializeToMono(monoWave, inputFiles[j]);  //initilize the converted wave with modified data
        if(wave->fmtChunk->numChannels == 1){
            printf("%s has MONO sound. Cannot convert\n", inputFiles[j] );  //check if wave is stereo
            goto Free;
        }

        for (i=0;i<wave->dataChunk->subchunk2Size; i=i+ (wave->fmtChunk->bitsPerSample)/4){ //loop throught every sample of reverse data
            memcpy(&monoWave->dataChunk->data[insertCounter], &wave->dataChunk->data[i], wave->fmtChunk->bitsPerSample/8);  //copy the left data of the original to the new wave
            insertCounter = insertCounter+wave->fmtChunk->bitsPerSample/8;  //move to the next left sample
        }
        exportWave(inputFiles[j], monoWave, "mono-");   //export the wave

        Free:
        insertCounter = 0;
        deallocWave(wave);
        deallocWave(monoWave);
        free(wave);
        free(monoWave);
    }
}



void initializeToMono(WAVE *wave, char *inputFile){
    
    initializeFromFile(wave,inputFile);     //copy the data from the original file
    wave->riffChunk->chunkSize = wave->riffChunk->chunkSize - wave->dataChunk->subchunk2Size/2; //calculate the new chunk size

    wave->fmtChunk->numChannels = (word)1;  //new number of channels = 1
    wave->fmtChunk->byteRate = wave->fmtChunk->byteRate/2;  //calculate new byte rate
    wave->fmtChunk->blockAlign = wave->fmtChunk->blockAlign/2;  //calculate new blockAlign

    int originalWaveSample = (wave->dataChunk->subchunk2Size) / (2 * (wave->fmtChunk->bitsPerSample / 8));  //caculate original wave sample
    wave->dataChunk->subchunk2Size = (originalWaveSample) * (wave->fmtChunk->bitsPerSample / 8);        //find the size of the converted data size
    free(wave->dataChunk->data);
    wave->dataChunk->data = (byte *)malloc(wave->dataChunk->subchunk2Size * sizeof(byte));  //malloc the data size
}

#ifndef DEBUGGING
#ifdef DEBUGMONO
#define DEBUGGING
int main(int argc, char *argv[]){
    stereoToMono(argv[1]);
    return 0;
}
#endif
#endif