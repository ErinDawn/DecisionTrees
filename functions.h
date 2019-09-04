
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <array>
#include "helperFunctions.h"

using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int countColumns(string line, string delim);

float pi(float sampleWithOption, float sampleSize);

float calcEntropy(float pi);

float calcEntropy(float pi1, float pi2);

float attributeEntropy(int pos, int neg, int sampleSize);

float infoGain(float setEntropy, float entropy1, float entropy2);

#endif //FUNCTIONS_H
