#include "decode.h"
#include "encode.h"
    
void decode(char *waveFile, int len, char *textFile){
    WAVE *wave = (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,waveFile);
    char *text = (char*)calloc(len,1);
    FILE *fp;
    fp = fopen(textFile, "wb");
    int *permutation;
    permutation=createPermutationFunction(wave->dataChunk->subchunk2Size/8, KEY);

    int i,u,x;
    for(i=0; i<(1+len)*8;i++){
        
    }
}