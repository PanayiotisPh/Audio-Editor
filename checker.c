#include "checker.h"


bool isNumber(char* str){
    for (int i = 0; str[i]!= '\0'; i++)
    {
        if (isdigit(str[i]) == 0)
              return false;
    }
    return true;
}


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
    WAVE *wave = NULL;
    wave= (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,fileName);   
    if(wave->fmtChunk->audioFormat!=1){
        printf("invalid file \"%s\": it seems to be compressed (PCM != 1)\n",fileName);
        deallocWave(wave);
        free(wave);
        return false; 
    }

    if(wave->fmtChunk->numChannels > 2){
        printf("invalid file \"%s\": file has more than 2 channels\n",fileName);
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
        if(isValidWaveFile(fileName)){
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
            printf("timings given are not in range of wave file's length, wave's length is %d seconds\n",waveTime);
            deallocWave(wave);
            free(wave);
            return false;
    }

    deallocWave(wave);
    free(wave);
    return true;        
    

}



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

bool txtFitsWav(char *wavFileName, char *txtFileName){
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
        fclose(tfp);
        printf("file \"%s\" is empty\n",txtFileName);
        return false;
    }

    if(textSize > wave->dataChunk->subchunk2Size/8){
        printf("cannot fit text file to wave file\n");
        return false;
    }

    return true;
}




#ifndef DEBUGGING
#ifdef DEBUGCHECKER
#define DEBUGGING

int main(int argc, char *argv[]){
    //ADD CODE HERE
}

#endif
#endif