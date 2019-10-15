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

// float roundFloat(float var) 
// {
//     var = (var*100);
//     cout << "Var * 100 = " << var << endl;
//     int temp = var;
//     cout << "Temp = var which = " << temp << endl;
//     var = temp * 1.0;
//     cout << "Var = temp, as a float again " << var << endl;
//     var = var / 100;
//     cout << "Var = var divided by 100, as a float again " << var << endl;
//     return var; 
// }

float pi(float sampleWithOption, float sampleSize){
    float  result = sampleWithOption / sampleSize;
    return result;
}

float calcEntropy(float pi){
    return -(pi * log2(pi));
}

float calcEntropy(float pi1, float pi2){    //Can take an array of pi, use a for loop to entropy and add
   return calcEntropy(pi1) + calcEntropy(pi2);
}

float attributeEntropy(int pos, int neg, int sampleSize){
    if (pos == 0 || neg == 0){ return 0;}   //if no positive class feature this attribute, return zero
    int subSample = pos + neg;
    float piPos, piNeg;
    piPos = pi(pos, subSample);
    piNeg = pi(neg, subSample);
    float temp = calcEntropy(piPos) + calcEntropy(piNeg);
    float result = temp * (pi(subSample, sampleSize));
    return result;
}

 // float altSetEntropy(int* posCounts, int subSample, int sampleSize){
    // if (pos == 0){ return 0;}   //if no positive class feature this attribute, return zero
    // //int subSample = pos + neg;
    // int neg = subSample - pos;
    // float piPos, piNeg;
    // piPos = pi(pos, subSample);
    // piNeg = pi(neg, subSample);
    // float temp = calcEntropy(piPos);
    // // float result = temp * (pi(subSample, sampleSize));  //extract this out to where function is called
    // //return result; ; 
    // return temp;
 // }



float calcInfoGain(float setEntropy, float entropy1, float entropy2, float entropy3, float entropy4, float entropy5){
    float gain = (setEntropy - entropy1 - entropy2 - entropy3 - entropy4 - entropy5);
    return gain;
}