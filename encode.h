/**
 * @file encode.h
 * @author Panayiotis Fotiadis 1031373
 * @brief used to encode a text file to a wav file
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ENCODE
#define ENCODE
#include "wave.h"
#ifndef KEY
#define KEY 585     //seed used in random
#endif

/**
 * @brief read a wav file and a text file, and based on a random table it places the text bits into the wav file
 * 
 * @param waveFile imports a wave file
 * @param textFile import a text file
 */
void encode(char *waveFile, char *textFile);

/**
 * @brief finds the bit in the specific location and returns it
 * 
 * @param m text file
 * @param n bit position
 * @return int bit
 */
int getBit(char *m, int n);

/**
 * @brief Create a table and shuffle it randomly
 * 
 * @param N size of data 
 * @param systemkey srand key
 * @return int* shuffled table
 */
int *createPermutationFunction(int N, unsigned int systemkey);


#endif