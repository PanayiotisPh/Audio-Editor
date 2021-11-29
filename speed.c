/**
 * @file speed.c
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief implements speed.h
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

/**
 * @brief multiplies the speed of the wave file
 * 
 * @param fileName 
 * @param speedMult 
 */
void changeSpeed(char *fileName, float speedMult){
    WAVE *wave = (WAVE*) malloc(sizeof(WAVE));
    initializeFromFile(wave,fileName);      //initialize wave file from file
    wave->fmtChunk->sampleRate *= speedMult;    //change sample Rate to fast forward or slow down
    exportWave(fileName,wave,"speed-"); //export file
    deallocWave(wave);      //free memory
    free(wave);
}