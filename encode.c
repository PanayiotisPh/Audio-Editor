#include "encode.h"

void encode(char *waveFile, char *textFile){
    char *text = (char*)calloc(sizeof(char),1);
    FILE *fp;
    fp = fopen(textFile, "r");
    int i=0;
    while(!foef(fp)){
        fscanf(fp,"%c", &text[i]);
        i++;
        text = (char*)realloc(text, i);
    }
    printf("%s\n", text);

}
int getBit(char *m, int n){


}
int *createPermutationFunction(int N, unsigned int systemkey){


}

int main(int argc, char *argv[]){
    encode(argv[1],argv[2]);
}