/**
 * @file wave.c
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @author Panagiotis Fotiadis (pfotia01@ucy.ac.cy)
 * @brief implements wave.h
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

#include "wave.h"


/**
 * @brief initializes a wave from a wavefile
 * 
 * @param wave allocate memory for wave before using the method
 * @param fileName .wav file name
 */
void initializeFromFile(WAVE *wave, char *fileName){
    FILE *fp = NULL;
    fp = fopen(fileName, "rb");  
    if(fp==NULL){
        printf("file could not be opened or not found\n");
        exit(-1);
    } 
    /** allocate memory for chunks */
   	wave->dataChunk = (DATA_CHUNK*)malloc(sizeof(DATA_CHUNK));
    wave->riffChunk = (RIFF_CHUNK*)malloc(sizeof(RIFF_CHUNK));
	wave->fmtChunk = (FMT_CHUNK*)malloc(sizeof(FMT_CHUNK));

    /**read from wave file */
    fread(wave->riffChunk,sizeof(RIFF_CHUNK),1,fp);
	fread(wave->fmtChunk,sizeof(FMT_CHUNK),1,fp);
	fread(wave->dataChunk,4+sizeof(dword),1,fp);
    
    /**allocate memory and read the data */
    wave->dataChunk->data= (byte*) malloc(wave->dataChunk->subchunk2Size);
    fread(wave->dataChunk->data,wave->dataChunk->subchunk2Size,1,fp);
    fclose(fp);
}

/**
 * @brief initialize/allocate moemory for a wave
 * 
 * @param wave 
 */
void initialize(WAVE *wave){
   	wave->dataChunk = (DATA_CHUNK*)malloc(sizeof(DATA_CHUNK));
    wave->riffChunk = (RIFF_CHUNK*)malloc(sizeof(RIFF_CHUNK));
	wave->fmtChunk = (FMT_CHUNK*)malloc(sizeof(FMT_CHUNK));

}


/**
 * @brief deallocate memory of the wave
 * 
 * @param wave 
 */
void deallocWave(WAVE *wave){
	free(wave->fmtChunk);
    free(wave->riffChunk);
    free(wave->dataChunk->data);
	free(wave->dataChunk);
}

/**
 * @brief export wave to a file
 * 
 * @param orgFileName original file name 
 * @param wave wave to export
 * @param prefix prefix to the original file name
 */
void exportWave(char *orgFileName, WAVE *wave, char *prefix){
    char *outputFile = NULL; //output file name
    /** creates output file name */
    outputFile = (char*)calloc(1,strlen(orgFileName)+strlen(prefix)+1);
    strcat(outputFile, prefix);
    strcat(outputFile, orgFileName);

    /** write wave file to file */
    FILE *outfp = fopen(outputFile,"wb");
    fwrite(wave->riffChunk,sizeof(RIFF_CHUNK),1,outfp);
    fwrite(wave->fmtChunk,sizeof(FMT_CHUNK),1,outfp);
    fwrite(wave->dataChunk,sizeof(byte)*4+sizeof(dword),1,outfp);
    fwrite(wave->dataChunk->data ,wave->dataChunk->subchunk2Size,1,outfp);
    
    fclose(outfp);
    free(outputFile);
}

#ifndef DEBUGGING
#ifdef DEBUGWAVE
#define DEBUGGING

int main(int argc, char *argv[]){
    printf("%s %ld",argv[1],sizeof(byte));
    fflush(stdout);
    WAVE *wav=NULL;
    wav=(WAVE*)malloc(sizeof(WAVE));
    // FILE *fp = NULL;
    // fp = fopen(argv[1], "rb");  
    // if(fp==NULL){
    //     printf("file could not be opened or not found\n");
    //     exit(-1);
    // } 
    initialize(wav,argv[1]);
    printf("chunkId %s\nformat %s\nsubchunk1id %s\nsamplerate %d\nsubchunk2id %s\n subchunk2size %d",wav->riffChunk->chunkId, wav->riffChunk->format, wav->fmtChunk->subchunk1Id,wav->fmtChunk->sampleRate,wav->dataChunk->subchunk2Id,wav->dataChunk->subchunk2Size);


}
#endif
#endif
    