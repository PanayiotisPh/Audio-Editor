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
    getBit(text,0);

}
int getBit(char *m, int n){
    int byteCal = n/8;
    int bitCal = (7-(n%8));
    int i,j;
    int bit = (m[byteCal]>>bitCal&1);
    for(i=0;i<strlen(m);i++){
        //for(j=0;j<)
        printf("%d",(m));
    }
    printf("\n%d\n",bit);
    return bit;

}
int *createPermutationFunction(int N, unsigned int systemkey){


}

int main(int argc, char *argv[]){
    encode(argv[1],argv[2]);
}