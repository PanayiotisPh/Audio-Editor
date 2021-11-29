/**
 * @file cut.h
 * @author Panayitis Fotiadis 1031373
 * @brief cut wave file
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
#ifndef CHOP
#define CHOP
#include "wave.h"

/**
 * @brief exports a trimmed wave file
 * 
 * @param files table of files, it uses only the first one.
 * @param numOfFiles number of files in **files
 * @param start start time of trimmed wave
 * @param end  end time of trimmed wave
 */
void cut(char **files, int numOfFiles, int start, int end);





#endif