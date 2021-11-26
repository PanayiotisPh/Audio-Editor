#include "wave.h"
#include "list.h"
#include "checker.h"

#ifndef DEBUGGING

int main(int argc, char *argv[]){
    int i;
    if (argc < 3 || checkOptions(argv))
    { //checks if the usage command given is valid
        printf("Usage: $./wavengine <-option> sound1.wav [ sound2.wav sound3.wav ...]\n\noptions:\n\t-list\n\t-mono\n\t-mix\n\t-chop\n\t-reverse\n\t-encodeText\n\t-decodeText");
        return -1;
    }
}

#endif