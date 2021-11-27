#include "StereoToMono.h"

void stereoToMono(char **inputFiles, int numOfFiles){
    WAVE *wave=NULL;

    WAVE *monoWave = NULL;

    int i,j;
    int insertCounter = 0;

    for(j=0;j<numOfFiles;j++){  
            printf("%s\n",inputFiles[j]);

        wave=(WAVE*)malloc(sizeof(WAVE));
        monoWave = (WAVE*) malloc(sizeof(WAVE));

        initializeFromFile(wave,inputFiles[j]);

        initializeFromFile(monoWave,inputFiles[j]);

        initializeMonoWave(monoWave, wave);

        for (i=0;i<wave->dataChunk->subchunk2Size; i=i+ (wave->fmtChunk->bitsPerSample)/4){
            memcpy(&monoWave->dataChunk->data[insertCounter], &wave->dataChunk->data[i], wave->fmtChunk->bitsPerSample/8);
            insertCounter = insertCounter+wave->fmtChunk->bitsPerSample/8;
        }
        createNewWave(inputFiles[j], monoWave);

        insertCounter = 0;
        deallocWave(wave);
        deallocWave(monoWave);
        wave = NULL;
        monoWave =NULL;
    }
}

void createNewWave(char *input, WAVE *monoWave){
    char *outputFile = NULL;
    printf("%s\n",input);

    outputFile = (char*)malloc(sizeof(input)+49495);
    strcat(outputFile, "mono-");
    strcat(outputFile, input);
    FILE *outfp = fopen(outputFile,"w");
    printf("%s\n",outputFile);
    fwrite(monoWave->riffChunk,sizeof(RIFF_CHUNK),1,outfp);
    fwrite(monoWave->fmtChunk,sizeof(FMT_CHUNK),1,outfp);
    fwrite(monoWave->dataChunk,sizeof(byte)*4+sizeof(dword),1,outfp);
    fwrite(monoWave->dataChunk->data ,monoWave->dataChunk->subchunk2Size,1,outfp);
    free(outputFile);
    fclose(outfp);
    
}

void initializeMonoWave(WAVE *monoWave, WAVE *wave){
    monoWave->riffChunk->chunkSize = monoWave->riffChunk->chunkSize/2;

    monoWave->fmtChunk->numChannels = (word)1;                                      
    monoWave->fmtChunk->byteRate = monoWave->fmtChunk->byteRate/2;
    monoWave->fmtChunk->blockAlign = monoWave->fmtChunk->blockAlign/2;

    int originalWaveSample = (monoWave->dataChunk->subchunk2Size) / ((wave->fmtChunk->numChannels) * (wave->fmtChunk->bitsPerSample / 8));
    monoWave->dataChunk->subchunk2Size = (originalWaveSample) * (wave->fmtChunk->bitsPerSample / 8);
    monoWave->dataChunk->data = (byte *)malloc(monoWave->dataChunk->subchunk2Size * sizeof(byte));
    printf("outta\n");
    fflush(stdout);
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