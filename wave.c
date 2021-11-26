#include "wave.h"
/**
 * @brief initializes a wave
 * 
 * @param wave allocate memory for wave before using the method
 * @param fp .wav file pointer
 */
void initialize(WAVE *wave, char *fileName){
    FILE *fp = NULL;
    fp = fopen(fileName, "rb");  
    if(fp==NULL){
        printf("file could not be opened or not found\n");
        exit(-1);
    } 
   	wave->dataChunk = (DATA_CHUNK*)malloc(sizeof(DATA_CHUNK));
    wave->riffChunk = (RIFF_CHUNK*)malloc(sizeof(RIFF_CHUNK));
	wave->fmtChunk = (FMT_CHUNK*)malloc(sizeof(FMT_CHUNK));

    fread(wave->riffChunk,sizeof(RIFF_CHUNK),1,fp);
	fread(wave->fmtChunk,sizeof(FMT_CHUNK),1,fp);
	fread(wave->dataChunk,4+sizeof(dword),1,fp);

    wave->dataChunk->data= (byte*) malloc(wave->dataChunk->subchunk2Size);
    fread(wave->dataChunk->data,wave->dataChunk->subchunk2Size,1,fp);

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
    