#include "decode.h"
#include "encode.h"
    
void decode(char *waveFile, int len, char *textFile){
    WAVE *wave = (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,waveFile);
    char* text = (char*)calloc(1,len+1);
    FILE *fp;
    fp = fopen(textFile, "w");
    int *permutation;
    permutation=createPermutationFunction(wave->dataChunk->subchunk2Size, KEY);

    int byte,bit,u,x;
    int textIndex=(1+len)*8;
    int permIndex=0;
    for(byte=0; byte<1+len;byte++){
        char c=NULL;
        for(bit=7; bit>=0;bit--){
            x=permutation[permIndex++];
            u= wave->dataChunk->data[x];
            c |= u << bit;
        }
        strncat(text,&c,1);
        c=NULL;
    }

    fprintf(fp,text);
    
    deallocWave(wave);
    free(wave);
    free(text);
}