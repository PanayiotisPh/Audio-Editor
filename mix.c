/**
 * @file mix.c
 * @author Panayiotis Fotiadis
 * @brief mixes 2 stereo waves into a new wav file
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
#include "mix.h"

void mixWaves(char **inputFiles, int numOfFiles){
    WAVE *wave1=NULL;
    WAVE *wave2 = NULL;
    WAVE *mixWaves = NULL;

    int i;
    if(numOfFiles != 2){        //check if the user imported only 2 files
        printf("Can not make a mix with %d waves. Import 2 files\n", numOfFiles);
        return;
    }

    //create waves files to fill them 
    wave1=(WAVE*)malloc(sizeof(WAVE));
    wave2 = (WAVE*) malloc(sizeof(WAVE));
    mixWaves =(WAVE*)malloc(sizeof(WAVE));

    initializeFromFile(wave1,inputFiles[0]);    //fill them with the data from text files
    initializeFromFile(wave2,inputFiles[1]);

    if(wave1->fmtChunk->numChannels != 2 || wave2->fmtChunk->numChannels != 2){ //check if both of them are stereo
        printf("Waves must be Stereo\n");
        deallocWave(wave1);
        deallocWave(wave2);
        goto Free;
    }
    if(wave1->fmtChunk->bitsPerSample != wave2->fmtChunk->bitsPerSample){   //check if they have the same bits per sample 
        printf("Waves must have the same BitsPerSample\n");
        deallocWave(wave1);
        deallocWave(wave2);
        goto Free;
    }

    int smallerChunkSize;

    if(wave1->dataChunk->subchunk2Size < wave2->dataChunk->subchunk2Size){  //find the smaller wave file and store its data size and copy its data to the mix file
        smallerChunkSize = wave1->dataChunk->subchunk2Size;
        createMixWave(mixWaves, inputFiles[0]);

    }
    else{
        smallerChunkSize = wave2->dataChunk->subchunk2Size;
        createMixWave(mixWaves, inputFiles[1]);
    }

    bool switchChannel = true;  //defines which channel to copy
    int insertCounterWave1 = wave1->fmtChunk->bitsPerSample/8;  //used to store the index of right channel
    int insertCounterWave2 = 0; //used to store the index of the left channel



    for (i=0;i<smallerChunkSize; i=i+ (wave1->fmtChunk->bitsPerSample)/8){ //loop throught the samples
        if(switchChannel){  //if file2
            memcpy(&mixWaves->dataChunk->data[i], &wave2->dataChunk->data[insertCounterWave2], wave2->fmtChunk->bitsPerSample/8);   //copy the left sample to the mixWave
            insertCounterWave2 = insertCounterWave2 + wave2->fmtChunk->bitsPerSample/4; //move the counter to next left sample
            switchChannel = false;  //switch channel
            continue;
        }
        else if(!switchChannel){    //if file 1
            memcpy(&mixWaves->dataChunk->data[i], &wave1->dataChunk->data[insertCounterWave1], wave1->fmtChunk->bitsPerSample/8);   //copy the right sample to mixWave
            insertCounterWave1 = insertCounterWave1 + wave1->fmtChunk->bitsPerSample/4; //move the counter to next right sample
            switchChannel = true;   //switch channel
            continue;
        }
    }

    char *outputfile = calloc(strlen(inputFiles[0]) + 6,1);
    strcat(outputfile,"mix-");  //create the text name file
    strcat(outputfile,inputFiles[0]);
    strcat(outputfile,"-");
    exportWave(inputFiles[1], mixWaves, outputfile); //export it 

    Free:
    deallocWave(wave1);
    deallocWave(wave2);
    wave1 = NULL;
    wave2 =NULL;
}


void createMixWave(WAVE *mixWave, char *inputFile){
    initializeFromFile(mixWave, inputFile);     //initialize the mixWave from file
    free(mixWave->dataChunk->data);     //free the data segment
    mixWave->dataChunk->data = (byte *)malloc(mixWave->dataChunk->subchunk2Size * sizeof(byte));    //malloc a free space to store the new data
}

#ifndef DEBUGGING
#ifdef DEBUGMIX
#define DEBUGGING

int main(int argc, char *argv[]){

}
#endif
#endif