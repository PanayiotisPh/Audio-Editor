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
    printf("%s\n", text);
    for(i=0;i<strlen(text)*8;i++){
        printf("%d",getBit(text,i));
    }

}
int getBit(char *m, int n){
    int byteCal = n/8;
    int bitCal = (7-(n%8));
    int i,j;
    int bit = (m[byteCal]>>bitCal&1);
    return bit;
}

int *createPermutationFunction(int N, unsigned int systemkey){


}


#ifndef DEBUGGING
#ifdef DEBUGENCODE
#define DEBUGGING

int main(int argc, char *argv[]){
    //ADD CODE HERE
}

#endif
#endif