#include "reverse.h"

void reverseWave(char **inputFiles, int numOfFiles){
    printf("amin\n");

    int i;
    WAVE *wave = NULL;
    for (i = 0; i < numOfFiles; i++){
        wave = (WAVE*)malloc(sizeof(WAVE));
        initializeFromFile(wave,inputFiles[i]);
        if(wave->fmtChunk->numChannels == 1){
            reverseMono(wave, inputFiles[i]);
        }
        // else{
        //     reverseStereo(wave, inputFiles[i]);
        // }
        deallocWave(wave);
        free(wave);
    }
    

}
// void reverseStereo(WAVE *wave, char *inputFile){

// }
void reverseMono(WAVE *wave, char *inputFile){
    printf("am ine");
    WAVE *reverseWave =NULL;
    reverseWave = (WAVE*)malloc(sizeof(WAVE));
    createReverseWave(reverseWave, inputFile);
    int i;
    int waveCounter = 0;
    for(i=wave->dataChunk->subchunk2Size- (wave->fmtChunk->bitsPerSample/8) ; i>=0; i = i-(wave->fmtChunk->bitsPerSample/8)){
        memcpy(&reverseWave->dataChunk->data[i], &wave->dataChunk->data[waveCounter], wave->fmtChunk->bitsPerSample/8);
        waveCounter = waveCounter + wave->fmtChunk->bitsPerSample/8;
        printf("%d\t%d\n", i, waveCounter);
    }
    exportWave(inputFile, reverseWave,"reverse-");
    deallocWave(reverseWave);
    reverseWave =NULL;
}

void createReverseWave(WAVE *reverseWave, char *inputFile){
    initializeFromFile(reverseWave, inputFile);
    free(reverseWave->dataChunk->data);
    reverseWave->dataChunk->data = (byte *)malloc(reverseWave->dataChunk->subchunk2Size * sizeof(byte));
}
