
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

// float InformationGain(float entropy[]);

#endif //FUNCTIONS_H
