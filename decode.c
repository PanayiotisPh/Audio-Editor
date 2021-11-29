/**
 * @file decode.c
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief implements decode.h
 * @version 0.1
 * @date 2021-11-29
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details in the COPYING file.
 *  
 * See license in COPYING file.
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "decode.h"
#include "encode.h"

 /**
  * @brief decodes an encoded text from a wavefile
  * 
  * @param waveFile wave file
  * @param len length of message
  * @param textFile output file
  */
void decode(char *waveFile, int len, char *textFile){
    WAVE *wave = (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,waveFile);
    char* text = (char*)calloc(1,len+1);
    FILE *fp;
    fp = fopen(textFile, "w");
    int *permutation;
    permutation=createPermutationFunction(wave->dataChunk->subchunk2Size, KEY);

    int byte,bit,u,x;
    int permIndex=0;
    /**
     * @brief builds a character and then inserts it to the text
     */
    for(byte=0; byte<1+len;byte++){
        char c=NULL;
        for(bit=7; bit>=0;bit--){ //builds character bit by bit
            x=permutation[permIndex++];
            u= wave->dataChunk->data[x];
            c |= u << bit;
        }
        strncat(text,&c,1);
        c=NULL;
    }

    fprintf(fp,text);
    fclose(fp);
    deallocWave(wave);
    free(wave);
    free(text);
}