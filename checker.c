/**
 * @file checker.c
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief implements checker.h
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

#include "checker.h"

/**
 * @brief checks if a string represents a number
 * 
 * @param str
 * @return true 
 * @return false 
 */
bool isNumber(char* str){
    for (int i = 0; str[i]!= '\0'; i++)
    {
        if (!isdigit(str[i]) && str[i]!='.')
              return false;
    }
    return true;
}


/**
 * @brief checks if the option from the command line is valid 
 * 
 * @param argv arguments from command line
 * @return true 
 * @return false 
 */
bool checkOption(char *argv[]){
        if(strcmp(argv[1],"-list")==0 || strcmp(argv[1],"-mono")==0 || strcmp(argv[1],"-mix")==0 || strcmp(argv[1],"-chop")==0 
        || strcmp(argv[1],"-reverse")==0 || strcmp(argv[1],"-encodeText")==0 || strcmp(argv[1],"-decodeText")==0 || strcmp(argv[1],"-changeSpeed")==0)
            return true;
     return false;    
}

/**
 * @brief checks if the wave file is valid
 * 
 * @param fileName wave file
 * @return true 
 * @return false 
 */
bool isValidWaveFile(char *fileName){
    if(isNumber(fileName))
        return false;

    int len = strlen(fileName);
    if(len<4){
        printf("invalid filename \"%s\": it's too short\n",fileName);
        return false;
    }
    char *fileExtension = &fileName[len-4];    
    if(strcmp(fileExtension,".wav")!=0){
        if(strcmp(fileExtension,".txt")==0)
            return false;
        printf("invalid filename \"%s\": it's not a .wav file\n",fileName);
        return false;
    }

    bool valid= true;
    WAVE *wave = NULL;
    wave= (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,fileName);   
    if(wave->fmtChunk->audioFormat!=1){
        printf("invalid file \"%s\": it seems to be compressed (PCM != 1)\n",fileName);
        valid = false;
        goto free;
    }

    if(wave->fmtChunk->numChannels > 2){
        printf("invalid file \"%s\": file has more than 2 channels\n",fileName);
        valid = false;
        goto free;

    }

    free:
    deallocWave(wave);
    free(wave);
    return valid;    
}

/**
 * @brief checks and returns the Valid Files from the argument line
 * 
 * @param argv arguments from command line
 * @param numOfValidFiles number of valid files
 * @return char** a teble with all valid files
 */
char **getValidFiles(char *argv[],int *numOfValidFiles){
    int i=2;
    int numOfFiles=0;
    numOfValidFiles[0]=0;
    while(argv[i]!=NULL){
        numOfFiles++;
        i++;
    }
    char **validFiles= malloc(numOfFiles*sizeof(char*));

    for(i=0;i<numOfFiles;i++){
        char *fileName=argv[2+i];
        if(isValidWaveFile(fileName)){
            validFiles[numOfValidFiles[0]]=fileName;
            numOfValidFiles[0]++;

        }           
    }

    return validFiles;
}

/**
 * @brief checks if the timings given are in range with the length of the wave file and 
 *        that the start time is smaller than the end time
 * 
 * @param fileName the name of the wave file
 * @param start the start time of chopping
 * @param end the end time of chopping
 * @return true 
 * @return false 
 */
bool checkTimings(char* fileName, int start, int end){
    if(start>end){
        printf("start time is bigger than end time\n");
        return false;
    } 
    bool valid = true;   
    WAVE *wave =(WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,fileName);
    int waveTime = (int) wave->dataChunk->subchunk2Size /(int) wave->fmtChunk->byteRate;
    if(start > waveTime || end > waveTime || start < 0|| end < 0 ){
            printf("timings given are not in range of wave file's length, wave's length is %d seconds\n",waveTime);
            valid = false;
            goto free;
    }

    free:
    deallocWave(wave);
    free(wave);
    return valid;           
}


/**
 * @brief checks if the file name has a .txt extension
 * 
 * @param fileName the .txt file
 * @return true 
 * @return false 
 */
bool isTextFile(char *fileName){
    if(isNumber(fileName))
        return false;

    int len = strlen(fileName);
    if(len<4){
        printf("invalid filename  \"%s\": it's too short\n",fileName);
        return false;
    }
    char *fileExtension = &fileName[len-4];    
    if(strcmp(fileExtension,".txt")!=0){
        printf("invalid file \"%s\": file extension is not .txt\n",fileName);
        return false;
    }
    return true;
}

/**
 * @brief check if the text file fits to get encoded in the wave file
 * 
 * @param wavFileName 
 * @param txtFileName 
 * @return true 
 * @return false 
 */
bool txtFitsWav(char *wavFileName, char *txtFileName){
    bool fits=true;
    FILE *tfp=NULL;
    tfp = fopen(txtFileName,"rb");
    if(tfp == NULL){
        printf("could not open file %s\n",txtFileName);
        return false;
    }
    WAVE *wave=(WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,wavFileName);
    int textSize=0;

    fseek(tfp,0,SEEK_END);
    textSize = ftell(tfp);       //count file size
    if (textSize == 0){     //check if file is empty and ouput a warning message
        printf("file \"%s\" is empty\n",txtFileName);
        fits=false;
        goto free;
    }
    /**
     * @brief bits in text file should not be more than the bytes in the data of the wave file
     */
    if(textSize*8 > wave->dataChunk->subchunk2Size){
        printf("cannot fit text file to wave file\n");
        fits=false;
        goto free;
    }
    free: 
    fclose(tfp);
    deallocWave(wave);
    free(wave);
    return fits;
}




#ifndef DEBUGGING
#ifdef DEBUGCHECKER
#define DEBUGGING

int main(int argc, char *argv[]){
    //ADD CODE HERE
}

#endif
#endif