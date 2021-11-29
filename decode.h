/**
 * @file decode.h
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @author Panagiotis Fotiadis (pfotia01@ucy.ac.cy)
 * @brief decodes a text from wave file
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


#ifndef DECODE
#define DECODE
#include "wave.h"
#ifndef KEY
#define KEY 585
#endif

 /**
  * @brief decodes an encoded text from a wavefile
  * 
  * @param waveFile wave file
  * @param len length of message
  * @param textFile output file
  */
void decode(char *waveFile, int len, char *textFile);



#endif

