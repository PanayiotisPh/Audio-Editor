#include "encode.h"

void encode(char *waveFile, char *textFile){
    FILE *fp =NULL;
    fp = fopen(textFile, "r");
    int size;       //used to store file size
    int row, column; //counts the row and columns of table
    fseek (fp, 0, SEEK_END);
    size = ftell(fp);       //count file size
    rewind(fp);     //restore the file pointer to the begining of it
    char *text = malloc(size);
    for (i = 0;i)




}
int getBit(char *m, int n){


}
int *createPermutationFunction(int N, unsigned int systemkey){


}