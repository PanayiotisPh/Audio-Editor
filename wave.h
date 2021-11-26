#ifndef WAVEH
#define WAVEH


typedef unsigned char byte; 
typedef unsigned short int word;  
typedef unsigned int dword; 


typedef struct riff_chunk 
{ 
    byte chunkId[4];
    word chunkSize;
    byte format[4];
 
} RIFF_CHUNK; 

typedef struct fmt_chunk 
{ 
    byte subchunk1Id[4];
    word subchunk1Size;
    byte audioFormat[2];
    byte numChannels[2];
    word sampleRate;
    word byteRate;
    byte blockAlign[2];
    byte bitsPerSample[2];
 
} FMT_CHUNK; 

typedef struct data_chunk 
{ 
    byte subchunk2Id[4];
    word subchunk2Size;
    byte* data;
 
} DATA_CHUNK; 




typedef struct wave
{ 
 RIFF_CHUNK *riffChunk; 
 FMT_CHUNK *fmtChunk;
 DATA_CHUNK *dataChunk;
}WAVE; 

void initialize(WAVE *wave);

#endif