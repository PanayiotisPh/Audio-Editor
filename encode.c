#include "encode.h"

void encode(char *waveFile, char *textFile){
    printf("%s\t%s\n",waveFile,textFile);
    char *text = (char*)calloc(sizeof(char),1);
    FILE *fp;
    fp = fopen(textFile, "r");
    int i=0;
    while(!feof(fp)){
        fscanf(fp,"%c", &text[i]);
        i++;
        text = (char*)realloc(text, i);
    }
    fclose(fp);
    printf("%ld\n", strlen(text));
    for(i=0;i<strlen(text)*8-1;i++){
        printf("%d",getBit(text,i));
    }
    WAVE *wave =NULL;
    wave = (WAVE*)malloc(sizeof(WAVE));
    initializeFromFile(wave, waveFile);
    int *permutation = malloc(wave->dataChunk->subchunk2Size);
    permutation = createPermutationFunction(wave->dataChunk->subchunk2Size, 5);
    for(i=0;i<10;i++)   
        printf("%d", permutation[i]);

}
int getBit(char *m, int n){
    int byteCal = n/8;
    int bitCal = (7-(n%8));
    int bit = (m[byteCal]>>bitCal&1);
    return bit;
}

int *createPermutationFunction(int N, unsigned int systemkey){
    printf("amin\n");
    int *permutation = (int*)malloc(N);
    int i,index1,index2,temp;
    srand(systemkey);
    for(i=0;i<N;i++){
        permutation[i]=i;
    }
    for (i=0;i<N;i++){
        index1 = rand();
        index2 = rand();
        temp = index1;
        index1 = index2;
        index2 = temp;
    }
    printf("*****************************\n");
     for(i=0;i<10;i++)   
        printf("%d", permutation[i]);
    return permutation;
}


#ifndef DEBUGGING
#ifdef DEBUGENCODE
#define DEBUGGING

int main(int argc, char *argv[]){
    encode(argv[1],argv[2]);
}

#endif
#endif