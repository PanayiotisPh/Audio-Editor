#include "decode.h"
#include "encode.h"
    
void decode(char *waveFile, int len, char *textFile){
    WAVE *wave = (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,waveFile);
    byte text[(len+1)];
    FILE *fp;
    fp = fopen(textFile, "wb");
    int *permutation;
    permutation=createPermutationFunction(wave->dataChunk->subchunk2Size/8, KEY);

    int byte,bit,u,x;
    int textIndex=(1+len)*8;
    for(byte=0; byte<1+len;byte++)
        for(bit=7; bit>=0;bit--){
            x=permutation[bit+byte*8];
            u= getBit(wave->dataChunk->data,x);
            text[byte]>>(bit&1) = u;
        }

    printf("text: %s",text);


}