#include "wave.h"
#include <stdio.h>
#include <stdlib.h>
void initialize(WAVE *wave, char *fileName){
    FILE *fp = fopen(fileName, "rb");   
    fread(wave,1,44,fp);
    wave->dataChunk->data= (byte*) malloc(wave->dataChunk->subchunk2Size);
    fread(wave,1,wave->dataChunk->subchunk2Size,fp);
}

int main(int argc, char *argv[]){
    printf("%s",argv[1]);
    fflush(stdout);
    WAVE *wav=NULL;
    wav=(WAVE*)malloc(sizeof(WAVE));
    initialize(wav,argv[1]);
    printf("chunkId %s\nformat %s\nsubchunk1id %s\nsamplerate %d\nsubchunk2id %s\n subchunk2size %d",wav->riffChunk->chunkId, wav->riffChunk->format, wav->fmtChunk->subchunk1Id,wav->fmtChunk->sampleRate,wav->dataChunk->subchunk2Id,wav->dataChunk->subchunk2Size);


}
