//Entropy - how much disorder in information a certain set contains.
// Entropy = sum of p of i log2 (p of i)

//Information Gain - How much information a particular bit of data gives us

#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <array>
#include "helperFunctions.h"

using namespace std;

float roundAlt(float var) 
{
    var = (var*100);
    int temp = var;
    var = temp * 1.0;
    var = var / 100;
    return var; 
}

float pi(float sampleWithOption, float sampleSize){
    float  result = sampleWithOption / sampleSize;
    return result;
}

float calcEntropy(float pi){
    if (pi == 0) {return 0;}
    return -(pi * log2(pi));
}

float calcEntropy(float pi1, float pi2){    //Can take an array of pi, use a for loop to entropy and add
   return calcEntropy(pi1) + calcEntropy(pi2);
}

float calcInfoGain(float setEntropy, float entropy1, float entropy2, float entropy3, float entropy4, float entropy5){
    float gain = (setEntropy - entropy1 - entropy2 - entropy3 - entropy4 - entropy5);
    return gain;
}