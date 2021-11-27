#include "checker.h"

/**
 * @brief checks if the option from the command line is valid 
 * 
 * @param argv 
 * @return true 
 * @return false 
 */
bool checkOption(char *argv[]){
        if(strcmp(argv[1],"-list")!=0 || strcmp(argv[1],"-mono")!=0 || strcmp(argv[1],"-mix")!=0 || strcmp(argv[1],"-chop")!=0 
        || strcmp(argv[1],"-reverse")!=0 || strcmp(argv[1],"-encodeText")!=0 || strcmp(argv[1],"-decodeText")!=0 )
            return false;
     return true;    
}

/**
 * @brief checks if the file name is valid
 * 
 * @param fileName 
 * @return true 
 * @return false 
 */
bool checkFileFormat(char *fileName){
    int len = strlen(fileName);
    if(len<4){
        //printf("invalid filename: it's too short\n");
        return false;
    }
    char *fileExtension = &fileName[len-4];    
    if(strcmp(fileExtension,".wav")!=0){
        printf("invalid filename: it's not a .wav file\n");
        return false;
    }
    WAVE *wave = NULL;
    wave= (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,fileName);   
    if(wave->fmtChunk->audioFormat!=1){
        printf("invalid filename: it's not PCM\n");
        deallocWave(wave);
        free(wave);
        return false; 
    }
    deallocWave(wave);
    free(wave);
    return true;    
}

/**
 * @brief checks and returns the Valid Files from the argument line
 * 
 * @param argv 
 * @return char** 
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
        if(checkFileFormat(fileName)){
            validFiles[numOfValidFiles[0]]=fileName;
            numOfValidFiles[0]++;

        }           
    }

    return validFiles;
}

bool checkTimings(char* fileName, int start, int end){
    if(start>end){
        printf("start time is bigger than end time\n");
        return false;
    }    
    WAVE *wave =(WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,fileName);
    int waveTime = (int) wave->dataChunk->subchunk2Size /(int) wave->fmtChunk->byteRate;
    if(start > waveTime || end > waveTime || start < 0|| end < 0 ){
            printf("timings given are not in range of wave file's length. wave's length is %d seconds\n",waveTime);
            return false;
    }
    return true;        
    

}

bool isNumber(char* str){
    for (int i = 0; str[i]!= '\0'; i++)
    {
        if (isdigit(str[i]) == 0)
              return false;
    }
    return true;
}