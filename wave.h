/**
 * @file wave.h
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief wave structure
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
#ifndef WAVEH
#define WAVEH
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char byte; 
typedef unsigned short int word;  
typedef unsigned int dword; 


typedef struct riff_chunk 
{ 
    byte chunkId[4];
    dword chunkSize;
    byte format[4];
 
} RIFF_CHUNK; 

typedef struct fmt_chunk 
{ 
    byte subchunk1Id[4];
    dword subchunk1Size;
    word audioFormat;
    word numChannels;
    dword sampleRate;
    dword byteRate;
    word blockAlign;
    word bitsPerSample;
 
} FMT_CHUNK; 

typedef struct data_chunk 
{ 
    byte subchunk2Id[4];
    dword subchunk2Size;
    byte* data;
 
} DATA_CHUNK; 




typedef struct wave
{ 
 RIFF_CHUNK *riffChunk; 
 FMT_CHUNK *fmtChunk;
 DATA_CHUNK *dataChunk;
}WAVE; 

/**
 * @brief initialize/allocate moemory for a wave
 * 
 * @param wave 
 */
void initialize(WAVE *wave);

/**
 * @brief initializes a wave from a wavefile
 * 
 * @param wave allocate memory for wave before using the method
 * @param fileName .wav file name
 */
void initializeFromFile(WAVE *wave,char *fileName);

/**
 * @brief deallocate memory of the wave
 * 
 * @param wave 
 */
void deallocWave(WAVE *wave);

/**
 * @brief export wave to a file
 * 
 * @param orgFileName original file name 
 * @param wave wave to export
 * @param prefix prefix to the original file name
 */
void exportWave(char *orgFileName, WAVE *wave, char *prefix);

#endif