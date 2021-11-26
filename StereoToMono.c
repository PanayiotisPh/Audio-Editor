#include "StereoToMono.h"

void stereoToMono(char *input, char *output){
    WAVE *wave=NULL;
    wave=(WAVE*)malloc(sizeof(WAVE));
    initialize(wave,input);
    int i;
    int counter = 0;
    int insertCounter = 0;
    bool readSample = true;
    byte *monoData;
    monoData = (byte*) malloc(wave->dataChunk->subchunk2Size/2);
    for (i=0;i<wave->dataChunk->subchunk2Size;i++){
        if(counter == wave->fmtChunk->bitsPerSample){
            counter = 0;
            readSample = !readSample;
        }
        if(readSample){
            monoData[insertCounter] = wave->dataChunk->data[i];
            insertCounter++;
        }
    }
    char *outputFile = NULL;
    outputFile = (char*)malloc(sizeof(output)+5);
    strcat(outputFile, "mono_");
    strcat(outputFile, output);
    FILE *outfp = fopen(outputFile,"w");
    /*
    bitsPerSample
    Subchunk2Size = All data bytes => size*8 => All data bits
    counter = 0
    bool = true
    for i until bits
    if counter == bitsPerSample{
        counter = 0
        bool = !bool
    }
    if(bool){
        data+= data[i]
    }
    counter++
    */

}