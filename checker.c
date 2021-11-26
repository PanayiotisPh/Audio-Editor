#include<stdbool.h>

bool checkOption(char *argv[]){
        if(strcmp(argv[1],"-list")!=0 || strcmp(argv[1],"-mono")!=0 || strcmp(argv[1],"-mix")!=0 || strcmp(argv[1],"-chop")!=0 
        || strcmp(argv[1],"-reverse")!=0 || strcmp(argv[1],"-encodeText")!=0 || strcmp(argv[1],"decodeText")!=0 )
            return false;
     return true;    
}