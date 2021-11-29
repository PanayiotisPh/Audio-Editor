/**
 * @file reverse.h
 * @author Panayiotis Fotiadis 1031373
 * @brief   reverse the data of the wave
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
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
 */

#ifndef REVERSE
#define REVERSE
#include "wave.h"

/**
 * @brief finds if the wave is stereo or mono and jumps to specific function
 * 
 * @param inputFiles stores all wave files
 * @param numOfFiles number of stored files
 */
void reverseWave(char **inputFiles, int numOfFiles);

/**
 * @brief reverse a stereo wave
 * 
 * @param wave original wave 
 * @param inputFile input file of original wave
 */
void reverseStereo(WAVE *wave, char *inputFile);

/**
 * @brief reverse a mono wave
 * 
 * @param wave original wave
 * @param inputFile input file of original wave
 */
void reverseMono(WAVE *wave, char *inputFile);

/**
 * @brief create the reverse wave with empty data
 * 
 * @param reverseWave wave to store the data
 * @param inputFile input file of original wave
 */
void createReverseWave(WAVE *reverseWave, char *inputFile);

#endif