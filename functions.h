
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include "helperFunctions.h"

using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int countColumns(string line, string delim);

float pi(int sampleWithOption, int sampleSize);

float entropy(float pi);

float entropy(float pi1, float pi2);

#endif //FUNCTIONS_H
