/**
 * @file speed.h
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief changes the speed of the wave file
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

#ifndef SPEED
#define SPEED
#include "wave.h"

/**
 * @brief multiplies the speed of the wave file
 * 
 * @param fileName 
 * @param speedMult 
 */
void changeSpeed(char *fileName, float speedMult);

#endif
