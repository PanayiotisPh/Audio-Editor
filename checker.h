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