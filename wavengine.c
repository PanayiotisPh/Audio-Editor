#include "wave.h"
#include "list.h"
#include "checker.h"
#include "StereoToMono.h"

#ifndef DEBUGGING
char* GPL= "\n This program is free software: you can redistribute it and/or modify\n it under the terms of the GNU General Public License as published by\n the Free Software Foundation, either version 3 of the License, or\n at your option) any later version.\n \n This program is distributed in the hope that it will be useful,\n but WITHOUT ANY WARRANTY; without even the implied warranty of\n MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n GNU General Public License for more details in the COPYING file.\n\n See license in COPYING file.";
char* usage="Usage: $./wavengine <-option> sound1.wav [ sound2.wav sound3.wav ...]\n\noptions:\n\t-list\n\t-mono\n\t-mix\n\t-chop\n\t-reverse\n\t-encodeText\n\t-decodeText";

int main(int argc, char *argv[]){
    int i;
    if (argc < 3 || checkOption(argv)){ //checks if the usage command given is valid
        printf("%s\n%s",GPL,usage);     
        return -1;
    }
    int *numOfValidFiles;
    numOfValidFiles = malloc(sizeof(int));
    numOfValidFiles[0]=0;
    char **validFiles= getValidFiles(argv,numOfValidFiles);
    char *option= argv[1];

    if(strcmp(option,"-list")==0){
        list(validFiles, numOfValidFiles[0]);
        goto free;
    }
    else if(strcmp(option,"-mono")==0){
        stereoToMono(validFiles, numOfValidFiles[0]);
        goto free;
    }
    else{
        goto free;
    }

    free:
        free(validFiles);    
        free(numOfValidFiles);
    return 0;

    



}

#endif