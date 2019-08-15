//Entropy - how much disorder in information a certain set contains.
// Entropy = sum of p of i log2 (p of i)

//Information Gain - How much information a particular bit of data gives us

#include <iostream>
#include <cmath>
#include <string>
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

float pi(int sampleWithOption, int sampleSize){
    //Pi = fraction of sample with option
    float  result;
    result = 1.0 * sampleWithOption / sampleSize;
    return result;
}

float entropy(float pi){
    return -(pi * log2(pi));
}

float entropy(float pi1, float pi2){
   return entropy(pi1) + entropy(pi2);
}


float InformationGain(int totalSamples, float membersOfSample1, float membersOfSample2){
    //Entropy of a set - (sample option / total sample * entropy of that option)
    //i.e.
    //Information gain for height where: total = 10, tall = 4, short = 6
    //  Entropy(height = 0.2 log2(0.2) + 0.8 log2(0.8))
    // entropy(height) - ((6/10)*Entropy(short)) - ((4/10)* Entropy(tall))
}

/*
* Function to build tree based on Info Gain
*/

