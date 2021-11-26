#include "wave.h"
#include <stdio.h>
void initialize(WAVE *wave, char *fileName){
    FILE *fp = fopen(fileName, "rb");
    fread(wave,1,44,fp);
    wave->dataChunk->data= (byte*) malloc(wave->dataChunk->subchunk2Size);
    fread(wave,1,wave->dataChunk->subchunk2Size,fp);
}

int main(int argc, char *argv[]){
    WAVE *wav=NULL;
    wav=(WAVE*)malloc(sizeof(WAVE));
    initialize(wav,)


}
