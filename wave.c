#include "wave.h"
#include <stdio.h>
#include <stdlib.h>
void initialize(WAVE *wave, char *fileName){
    wave=(WAVE*)malloc(sizeof(WAVE));
   	wave->dataChunk = (DATA_CHUNK*)malloc(sizeof(DATA_CHUNK));
    wave->riffChunk = (RIFF_CHUNK*)malloc(sizeof(RIFF_CHUNK));
	wave->fmtChunk = (FMT_CHUNK*)malloc(sizeof(FMT_CHUNK));
    readWave(wave,fileName);

}

void readWave(WAVE *wave, char *fileName){
    FILE *fp = NULL
    FILE *fp = fopen(fileName, "rb");  
    if(fp==NULL){
        printf("file could not be opened or not found\n");
        exit(-1);
    } 
    fread(wave,44,1,fp);
    wave->dataChunk->data= (byte*) malloc(wave->dataChunk->subchunk2Size);
    fread(wave,wave->dataChunk->subchunk2Size,1,fp);
}

int main(int argc, char *argv[]){
    printf("%s",argv[1]);
    fflush(stdout);
    WAVE *wav=NULL;
    
    initialize(wav,argv[1]);
    printf("chunkId %s\nformat %s\nsubchunk1id %s\nsamplerate %d\nsubchunk2id %s\n subchunk2size %d",wav->riffChunk->chunkId, wav->riffChunk->format, wav->fmtChunk->subchunk1Id,wav->fmtChunk->sampleRate,wav->dataChunk->subchunk2Id,wav->dataChunk->subchunk2Size);


}
    