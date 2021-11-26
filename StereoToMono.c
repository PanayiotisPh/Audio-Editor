#include "StereoToMono.h"

void stereoToMono(char *input, char *output){
    FILE *fp = NULL;
    fp = fopen(input, "rb");  
    if(fp==NULL){
        printf("file could not be opened or not found\n");
        exit(-1);
    }
    WAVE *wave=NULL;
    wave=(WAVE*)malloc(sizeof(WAVE));
    initialize(wave,fp);
    int i;

}