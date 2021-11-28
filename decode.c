#include "decode.h"
#include "encode.h"
    
void decode(char *waveFile, char *textFile){
    WAVE *wave = (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,waveFile);
    char *text = (char*)calloc(sizeof(char),1);
    FILE *fp;
    fp = fopen(textFile, "r");
    int i=0;
    while(!feof(fp)){
        fscanf(fp,"%c", &text[i]);
        i++;
        text = (char*)realloc(text, i);
    }
    printf("%ld\n", strlen(text));
    for(i=0;i<strlen(text)*8;i++){
        printf("%d",getBit(text,i));
    }

    int *permutation;
    permutation=createPermutationFunction(wave->dataChunk->subchunk2Size/8, KEY);

}