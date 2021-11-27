#ifndef WAVEH
#define WAVEH
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

void initialize(WAVE *wave);
void initializeFromFile(WAVE *wave,char *fileName);
void deallocWave(WAVE *wave);
// void readWave(WAVE *wave, FILE *fp);

#endif