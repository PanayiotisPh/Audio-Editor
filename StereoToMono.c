#include "StereoToMono.h"

void stereoToMono(char *input, char *output){
    WAVE *wave=NULL;
    wave=(WAVE*)malloc(sizeof(WAVE));
    initializeFromFile(wave,input);
    int i;
    int counter = 0;
    int insertCounter = 0;
    bool readSample = true;
    WAVE *monoWave = NULL;
    initializeMonoWave(monoWave, wave);
    for (i=0;i<wave->dataChunk->subchunk2Size;i++){
        if(counter == wave->fmtChunk->bitsPerSample){
            counter = 0;
            readSample = !readSample;
        }
        if(readSample){
            monoWave->dataChunk->data[insertCounter] = wave->dataChunk->data[i];
            insertCounter++;
        }
    }
   


    char *outputFile = NULL;
    outputFile = (char*)malloc(sizeof(output)+5);
    strcat(outputFile, "mono_");
    strcat(outputFile, output);
    FILE *outfp = fopen(outputFile,"w");

    fwrite(monoWave->riffChunk,sizeof(RIFF_CHUNK),1,outfp);
    fwrite(wave->fmtChunk,sizeof(FMT_CHUNK),1,outfp);
    fwrite(wave->dataChunk,sizeof(byte)*4+sizeof(dword),1,outfp);
    fwrite(&wave->dataChunk->data ,wave->dataChunk->subchunk2Size,1,outfp);
    
}

void initializeMonoWave(WAVE *monoWave, WAVE *wave){
    monoWave->dataChunk = (DATA_CHUNK*)malloc(sizeof(DATA_CHUNK));
    monoWave->riffChunk = (RIFF_CHUNK*)malloc(sizeof(RIFF_CHUNK));
	monoWave->fmtChunk = (FMT_CHUNK*)malloc(sizeof(FMT_CHUNK)); 

    strcpy((char *)monoWave->riffChunk->chunkId, (char *)wave->riffChunk->chunkId);
    monoWave->riffChunk->chunkSize = wave->riffChunk->chunkSize/2;
    strcpy((char *)wave->riffChunk->format, (char *)monoWave->riffChunk->format);

    //Copy FMT SUB-CHUNK
    strcpy((char *)monoWave->fmtChunk->subchunk1Id, (char *)wave->fmtChunk->subchunk1Id);
    monoWave->fmtChunk->subchunk1Size = wave->fmtChunk->subchunk1Size;
    monoWave->fmtChunk->audioFormat = wave->fmtChunk->audioFormat;
    monoWave->fmtChunk->numChannels = (word)1;                                      
    monoWave->fmtChunk->sampleRate = wave->fmtChunk->sampleRate;
    monoWave->fmtChunk->bitsPerSample = wave->fmtChunk->bitsPerSample;
    monoWave->fmtChunk->byteRate = (wave->fmtChunk->sampleRate) * 1 * (wave->fmtChunk->bitsPerSample / 8);
    monoWave->fmtChunk->blockAlign = 1 * (wave->fmtChunk->bitsPerSample / 8);

    //Copy DATA SUB-CHUNK  CHANGE LATER ASAP
    strcpy((char *)monoWave->dataChunk->subchunk2Id, (char *)wave->dataChunk->subchunk2Id);
    int OldNumSample = (wave->dataChunk->subchunk2Size) / ((wave->fmtChunk->numChannels) * (wave->fmtChunk->bitsPerSample / 8));
    monoWave->dataChunk->subchunk2Size = (OldNumSample)*1 * (wave->fmtChunk->bitsPerSample / 8);    //mono subchunk2size
    monoWave->dataChunk->data = (byte *)malloc(wave->dataChunk->subchunk2Size * sizeof(byte));
}

int main(int argc, int *argv){

}