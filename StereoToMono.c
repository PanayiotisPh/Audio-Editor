#include "StereoToMono.h"
#include "list.h"

void stereoToMono(char *input, char *output){
    WAVE *wave=NULL;
    wave=(WAVE*)malloc(sizeof(WAVE));
    initializeFromFile(wave,input); displayInfo(wave);
    int i;
    int insertCounter = 0;
    WAVE *monoWave = NULL;
    monoWave = (WAVE*) malloc(sizeof(WAVE));
    initializeMonoWave(monoWave, wave);
    for (i=0;i<wave->dataChunk->subchunk2Size; i=i+ (wave->fmtChunk->bitsPerSample)/4){
        memcpy(&monoWave->dataChunk->data[insertCounter], &wave->dataChunk->data[i], wave->fmtChunk->bitsPerSample/8);
        insertCounter = insertCounter+wave->fmtChunk->bitsPerSample/8;
    }
    displayInfo(monoWave);
    printf("\n\n");
    displayInfo(wave);

    

    char *outputFile = NULL;
    outputFile = (char*)malloc(sizeof(output)+5);
    strcat(outputFile, "mono_");
    strcat(outputFile, output);
    FILE *outfp = fopen(outputFile,"w");

    fwrite(monoWave->riffChunk,sizeof(RIFF_CHUNK),1,outfp);
    fwrite(wave->fmtChunk,sizeof(FMT_CHUNK),1,outfp);
    fwrite(wave->dataChunk,sizeof(byte)*4+sizeof(dword),1,outfp);
    fwrite(&wave->dataChunk->data ,wave->dataChunk->subchunk2Size,1,outfp);
    fclose(outfp);
    
}

void initializeMonoWave(WAVE *monoWave, WAVE *wave){
    monoWave->dataChunk = (DATA_CHUNK*)malloc(sizeof(DATA_CHUNK));
    monoWave->riffChunk = (RIFF_CHUNK*)malloc(sizeof(RIFF_CHUNK));
	monoWave->fmtChunk = (FMT_CHUNK*)malloc(sizeof(FMT_CHUNK)); 

    strcpy((char *)monoWave->riffChunk->chunkId, (char *)wave->riffChunk->chunkId);
    monoWave->riffChunk->chunkSize = wave->riffChunk->chunkSize/2;
    strcpy((char *)monoWave->riffChunk->format, (char *)wave->riffChunk->format);

    //Copy FMT SUB-CHUNK
    strcpy((char *)monoWave->fmtChunk->subchunk1Id, (char *)wave->fmtChunk->subchunk1Id);
    monoWave->fmtChunk->subchunk1Size = wave->fmtChunk->subchunk1Size;
    monoWave->fmtChunk->audioFormat = wave->fmtChunk->audioFormat;
    monoWave->fmtChunk->numChannels = (word)1;                                      
    monoWave->fmtChunk->sampleRate = wave->fmtChunk->sampleRate;
    monoWave->fmtChunk->bitsPerSample = wave->fmtChunk->bitsPerSample;
    monoWave->fmtChunk->byteRate = wave->fmtChunk->byteRate;
    monoWave->fmtChunk->blockAlign = wave->fmtChunk->blockAlign/2;

    //Copy DATA SUB-CHUNK  CHANGE LATER ASAP
    strcpy((char *)monoWave->dataChunk->subchunk2Id, (char *)wave->dataChunk->subchunk2Id);
    int OldNumSample = (wave->dataChunk->subchunk2Size) / ((wave->fmtChunk->numChannels) * (wave->fmtChunk->bitsPerSample / 8));
    monoWave->dataChunk->subchunk2Size = (OldNumSample)*1 * (wave->fmtChunk->bitsPerSample / 8);    //mono subchunk2size
    monoWave->dataChunk->data = (byte *)malloc(monoWave->dataChunk->subchunk2Size * sizeof(byte));
}

#ifndef DEBUGGING
#ifdef DEBUGMONO
#define DEBUGGING
int main(int argc, char *argv[]){
    stereoToMono(argv[1], argv[2]);
    return 0;
}
#endif
#endif