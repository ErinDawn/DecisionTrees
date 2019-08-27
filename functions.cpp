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
    //Pi = fraction of sample with option
   // float optionFloat = sampleWithOption * 1.0; //convert ints to floats
   // float sampleFloat = sampleSize * 1.0;
    float  result = sampleWithOption / sampleSize;
    return result;
}

float calcEntropy(float pi){
    return -(pi * log2(pi));
}

float calcEntropy(float pi1, float pi2){
   return calcEntropy(pi1) + calcEntropy(pi2);
}


// float InformationGain(float entropySet, entropyOption[]){
//     //InfoGain = EntropyOfSet - (sample option / total sample * entropy of that option)
//     //i.e.
//     //Information gain for height where: total = 10, tall = 4, short = 6
//     //  Entropy(height = 0.2 log2(0.2) + 0.8 log2(0.8))
//     // entropy(height) - ((6/10)*Entropy(short)) - ((4/10)* Entropy(tall))

//     float sumOfEntropy = 0.0;
//     float result = 0.0;
//     int length = entropyOption.size();
//     for (int i = 0; i < length; i++){
//         sumOfEntropy = entropyOption[i] + sumOfEntropy;
//     }
//     result = entropySet - sumOfEntropy;
//     return result;
// }

/*
* Function to build tree based on Info Gain
*/

