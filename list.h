/**
 * @file list.h
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief lists to the display all the headers of the wave files given in the argument line
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

#ifndef LIST
#define LIST
#include "wave.h"

/**
 * @brief lists to the display all the headers of the wave files given in the argument line
 * 
 * @param files 
 * @param numOfFiles 
 */
void list(char **files, int numOfFiles);

/**
 * @brief prints header to the screen
 * 
 * @param wave 
 */
void displayInfo(WAVE *wave);



#endif
