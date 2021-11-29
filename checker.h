/**
 * @file checker.h
 * @author Nikolas Theodorou (ntheod10@ucy.ac.cy)
 * @brief checks arguments for all functions
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

#ifndef CEHCKER
#define CHECKER
#include "wave.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief checks if a string represents a number
 * 
 * @param str
 * @return true 
 * @return false 
 */
bool isNumber(char *str);

/**
 * @brief checks if the option from the command line is valid 
 * 
 * @param argv arguments from command line
 * @return true 
 * @return false 
 */
bool checkOption(char *argv[]);

/**
 * @brief checks if the wave file is valid
 * 
 * @param fileName wave file
 * @return true 
 * @return false 
 */
bool isValidWaveFile(char *fileName);

/**
 * @brief checks and returns the Valid Files from the argument line
 * 
 * @param argv arguments from command line
 * @param numOfValidFiles number of valid files
 * @return char** a teble with all valid files
 */
char **getValidFiles(char *argv[], int *numOfValidFiles);

/**
 * @brief checks if the timings given are in range with the length of the wave file and 
 *        that the start time is smaller than the end time
 * 
 * @param fileName the name of the wave file
 * @param start the start time of chopping
 * @param end the end time of chopping
 * @return true 
 * @return false 
 */
bool checkTimings(char *fileName, int start, int end);

/**
 * @brief checks if the file name has a .txt extension
 * 
 * @param fileName the .txt file
 * @return true 
 * @return false 
 */
bool isTextFile(char *fileName);

/**
 * @brief check if the text file fits to get encoded in the wave file
 * 
 * @param wavFileName 
 * @param txtFileName 
 * @return true 
 * @return false 
 */
bool txtFitsWav(char *wavFileName, char *txtFileName);

#endif