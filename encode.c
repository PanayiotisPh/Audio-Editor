/**
 * @file encode.c
 * @author Panayiotis Fotiadis 1031373
 * @brief   used to encode a text file to a wav file
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
 * @copyright Copyright (c) 2021
 * 
 */
#include "encode.h"

void encode(char *waveFile, char *textFile){
    char *text = (char*)calloc(sizeof(char),1); //used to store text containt

    FILE *fp;
    fp = fopen(textFile, "r");  //read text
    int i=0;
    while(!feof(fp)){
        fscanf(fp,"%c", &text[i]);
        i++;
        text = (char*)realloc(text, i); //fill text with textFile containt
    }
    fclose(fp);
    
    WAVE *wave =NULL;
    wave = (WAVE*)malloc(sizeof(WAVE));
    initializeFromFile(wave, waveFile); //create WAVE and fill it with waveFile data
    int *permutation;
    permutation = createPermutationFunction(wave->dataChunk->subchunk2Size, KEY); //get table with shuffled positions
    
    int u,x;
    for(i=0;i<(1+strlen(text))*8;i++){  
        u = getBit(text,i); //get next bit of string
        x = permutation[i]; //get the position that the bit will be stored 
        wave->dataChunk->data[x]=u; //store the bit in the wave data
    }
    exportWave(waveFile,wave,"encoded-");   //export the encoded wave
}

int getBit(char *m, int n){
    int byteCal = n/8;  //calculate the byte that the bit it looks for exist
    int bitCal = (7-(n%8)); //calculate the position of the bit in the specific byte
    int bit = (m[byteCal]>>bitCal&1);   //shift the byte to the specific bit and save its value
    return bit; //return the bit
}

int *createPermutationFunction(int N, unsigned int systemkey){
    int *permutation = (int*)malloc(N*sizeof(int)); //used to store the shuffled numbers
    int i,index1,index2,temp;   //i used for loops, index1 and index2 are the position of numbers that will get swapped
    srand(systemkey);   //create srand with systemkey
    for(i=0;i<N;i++){
        permutation[i]=i;   //fill permutation
    }
    for (i=0;i<N;i++){
        index1 = rand() % N-1;
        index2 = rand() % N-1;
        temp = permutation[index1];     //create 2 random ints and swap number their indexes 
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