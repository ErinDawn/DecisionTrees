//Entropy - how much disorder in information a certain set contains.
// Entropy = sum of p of i log2 (p of i)

//Information Gain - How much information a particular bit of data gives us

#include <iostream>
#include <cmath>
#include <string>
#include <array>
#include "helperFunctions.h"

using namespace std;


//Will my data have headers? If so, process may change slightly, current data samples indicate no
//Alternately, can I have these entered by the user?
int countColumns(string line, string delim){
    int length = line.length();
    int features = 0;

    size_t pos = 0;
    string token;
    while ((pos = line.find(delim)) != string::npos) {
        token = line.substr(0, pos);
        trim(token);
        cout << token << endl;
        line.erase(0, pos + delim.length());
        features++;
    }
    trim(line);
    cout << line << endl << endl;

    return features;

}

float pi(float sampleWithOption, float sampleSize){
    float  result = sampleWithOption / sampleSize;
    return result;
};

float calcEntropy(float pi){
    return -(pi * log2(pi));
};

float calcEntropy(float pi1, float pi2){    //Can take an array of pi, use a for loop to entropy and add
   return calcEntropy(pi1) + calcEntropy(pi2);
};

float attributeEntropy(int pos, int neg, int sampleSize){
    int subSample = pos + neg;
    float piPos, piNeg;
    piPos = pi(pos, subSample);
    piNeg = pi(neg, subSample);
    float temp = calcEntropy(piPos, piNeg);
    float result = temp * (pi(subSample, sampleSize));
    return result; 
};

float infoGain(float setEntropy, float entropy1, float entropy2){
    float gain = setEntropy - entropy1 - entropy2;
    return gain;
};
