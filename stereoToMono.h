/**
 * @file stereoToMono.c
 * @author Panayiotis Fotiadis 1031373
 * @brief converts a wave from stereo to mono 
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

#ifndef STEREOTOMONO
#define STEREOTOMONO
#include "wave.h"

/**
 * @brief converts the wave in the inputFile from stereo to mono
 * 
 * @param inputFiles    waves to be converted
 * @param numOfFiles    number of files to be converted
 */
void stereoToMono(char **inputFiles, int numOfFiles);

/**
 * @brief initilize the data in the wave 
 * 
 * @param wave  new wave to store the data
 * @param inputFile     origianl wave data
 */
void initializeToMono(WAVE *wave, char *inputFile);



#endif