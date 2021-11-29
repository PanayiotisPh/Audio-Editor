/**
 * @file wavengine.c.c
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief this is the client of the program reads and checks options and the files of the argument line and then executes the program
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

#include "wave.h"
#include "list.h"
#include "checker.h"
#include "stereoToMono.h"
#include "chop.h"
#include "mix.h"
#include "reverse.h"
#include "encode.h"
#include "decode.h"
#include "speed.h"
#include "cut.h"

#ifndef DEBUGGING
char* GPL= "\n This program is free software: you can redistribute it and/or modify\n it under the terms of the GNU General Public License as published by\n the Free Software Foundation, either version 3 of the License, or\n at your option) any later version.\n \n This program is distributed in the hope that it will be useful,\n but WITHOUT ANY WARRANTY; without even the implied warranty of\n MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n GNU General Public License for more details in the COPYING file.\n\n See license in COPYING file.";
char* usage="Usage: $./wavengine <-option> sound1.wav [ sound2.wav sound3.wav ...]\n\noptions:\n\t-list\n\t-mono\n\t-mix\n\t-chop\n\t-reverse\n\t-encodeText\n\t-decodeText\n\t-changeSpeed\n";

/**
 * @brief this is the client of the program reads and checks options and the files of the argument line and then executes the program
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]){
    int i;
    if (argc < 3 || checkOption(argv)){ //checks if the usage command given is valid
        printf("%s\n%s",GPL,usage);     
        return -1;
    }
    int *numOfValidFiles;
    numOfValidFiles = malloc(sizeof(int));
    numOfValidFiles[0]=0;
    char **validFiles= getValidFiles(argv,numOfValidFiles); //check if files imported are valid
    char *option= argv[1];
   
    if(validFiles[0]==NULL){       //check if there are valid files
        printf("no valid wave files given\n");
        goto free;
    }    
    if(strcmp(option,"-list")==0){      //if option is list execute -list option
        list(validFiles, numOfValidFiles[0]);
        goto free;
    }
    if(strcmp(option,"-mono")==0){      //if option is list execute -mono option
        stereoToMono(validFiles, numOfValidFiles[0]);
        goto free;
    }
    if(strcmp(option,"-mix")==0){       //if option is list execute -mix option
        mixWaves(validFiles,numOfValidFiles[0]);
        goto free;
    }
    if(strcmp(option,"-chop")==0){      //if option is list execute -chop option
        if(numOfValidFiles[0]!=1 || !isNumber(argv[3]) || !isNumber(argv[4]) ){     //check if arguments are correct (wav file and 2 numbers)
            printf("invalid arguments, please enter only 1 valid .wav file and 2 integers for the seconds' margin\n");
            goto free;
        }
        
        int start = atoi(argv[3]);  //convert numbers from int to char
        int end = atoi(argv[4]);
        if(checkTimings(validFiles[0],start,end)){  //check if time to chop are valid
            chop(validFiles,numOfValidFiles[0],start,end);
            
        }else{
            printf("invalid timings given\n");
        }
        goto free; 
    }

    if(strcmp(option,"-reverse")==0){   //if option is list execute -reverse option
        reverseWave(validFiles,numOfValidFiles[0]);
        goto free;
    }

    if(strcmp(option,"-encodeText")==0){    //if option is list execute -encodeText option
        if(!isTextFile(argv[3]))        //check if the imported file is wav
            goto free;
        if(!txtFitsWav(validFiles[0],argv[3]))  //check if txt fits wav file
            goto free;
        encode(validFiles[0],argv[3]);
        goto free;

    }

    if(strcmp(option,"-decodeText")==0){        //if option is list execute -decodeText option
        if(!isNumber(argv[3]))
            goto free;
        if(!isTextFile(argv[4]))
            goto free;

        decode(validFiles[0],atoi(argv[3]),argv[4]);
        goto free;
    }  

     if(strcmp(option,"-changeSpeed")==0){
        if(!isNumber(argv[3]))
            goto free;

        changeSpeed(validFiles[0],atof(argv[3]));
        goto free;
    }  

    if(strcmp(option,"-cut")==0){      //if option is list execute -chop option
        if(numOfValidFiles[0]!=1 || !isNumber(argv[3]) || !isNumber(argv[4]) ){     //check if arguments are correct (wav file and 2 numbers)
            printf("invalid arguments, please enter only 1 valid .wav file and 2 integers for the seconds' margin\n");
            goto free;
        }
        
        int start = atoi(argv[3]);  //convert numbers from int to char
        int end = atoi(argv[4]);
        if(checkTimings(validFiles[0],start,end)){  //check if time to chop are valid
            cut(validFiles,numOfValidFiles[0],start,end);
            
        }else{
            printf("invalid timings given\n");
        }
        goto free; 
    }


    free:
        free(validFiles);    
        free(numOfValidFiles);
    return 0;
}

#endif