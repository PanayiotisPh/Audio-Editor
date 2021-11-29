#include "encode.h"

void encode(char *waveFile, char *textFile){
    char *text = (char*)calloc(sizeof(char),1); //used to store text containt
    FILE *fp;
    fp = fopen(textFile, "r");  //open
    int i=0;
    while(!feof(fp)){
        fscanf(fp,"%c", &text[i]);
        i++;
        text = (char*)realloc(text, i);
    }
    fclose(fp);
    printf("%ld\n", strlen(text));
    for(i=0;i<strlen(text)*8+8;i++){
        printf("%d",getBit(text,i));
    }
    printf("\nasDGrg\n");
    WAVE *wave =NULL;
    wave = (WAVE*)malloc(sizeof(WAVE));
    initializeFromFile(wave, waveFile);
    int *permutation /*= malloc(wave->dataChunk->subchunk2Size)*/; //axriasto na kameis malloc dame afou kameis malloc sti synartisi pio katw
    permutation = createPermutationFunction(wave->dataChunk->subchunk2Size, KEY); //dame thelei to KEY oxi 5
    
    int u,x;
    for(i=0;i<(1+strlen(text))*8;i++){
        u = getBit(text,i);
        x = permutation[i];
        wave->dataChunk->data[x]=u;
    }
    exportWave(waveFile,wave,"encoded-");

}
int getBit(char *m, int n){
    int byteCal = n/8;
    int bitCal = (7-(n%8));
    int bit = (m[byteCal]>>bitCal&1);
    return bit;
}

int *createPermutationFunction(int N, unsigned int systemkey){
    int *permutation = (int*)malloc(N*sizeof(int));
    int i,index1,index2,temp;
    srand(systemkey);
    for(i=0;i<N;i++){
        permutation[i]=i;
    }
    for (i=0;i<N;i++){
        index1 = rand() % N-1;
        index2 = rand() % N-1;
        temp = permutation[index1];
        permutation[index1] = permutation[index2];
        permutation[index2] = temp;
    }
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