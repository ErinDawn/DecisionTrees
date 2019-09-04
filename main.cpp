#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include "helperFunctions.h"
#include "functions.h"
#include "dataInfo.h"

using namespace std;

int main() {
int n_samples;
    int n_features;
    int n_classes;

    //Delete the following manual load in********************************************
    n_samples = 10;
    n_features = 2;
    n_classes = 2;
    string featureList[n_features];
    string classList[n_classes];


    featureList[0] = "height";
    featureList[1] = "dexterity";
    classList[0] = "yes";
    classList[1] = "no";
    //*******************************************************************************

    string dataArray[n_samples][n_features];
    string target[n_samples];
    
    //Refactor below - Load data in using function***********************************
    //read in the data to each corresponding place in the arrays
    dataArray[0][0] = "tall";
    dataArray[0][1] = "good";
    dataArray[1][0] = "short";
    dataArray[1][1] = "bad";
    dataArray[2][0] = "tall";
    dataArray[2][1] = "bad";
    dataArray[3][0] = "short";
    dataArray[3][1] = "bad";
    dataArray[4][0] = "tall";
    dataArray[4][1] = "good";
    dataArray[5][0] = "short";
    dataArray[5][1] = "good";
    dataArray[6][0] = "tall";
    dataArray[6][1] = "bad";
    dataArray[7][0] = "short";
    dataArray[7][1] = "bad";
    dataArray[8][0] = "short";
    dataArray[8][1] = "good";
    dataArray[9][0] = "short";
    dataArray[9][1] = "bad";

    target[0] = "yes";
    target[1] = "no";
    target[2] = "no";
    target[3] = "no";
    target[4] = "no";
    target[5] = "no";
    target[6] = "no";
    target[7] = "no";
    target[8] = "yes";
    target[9] = "no";
    //Refactor above**********************************************************

    //calc the entropy of set.
    int positiveCount = 0;
    int negativeCount = 0;
    int subSet = n_samples;

    //Calculate the positive members of the set
    for (int i = 0; i < subSet; i++){
        if ("yes" == target[i]){
            positiveCount++;
        }
    }

    //calcualte the negative members of the set
    for (int i = 0; i < subSet; i++){
        if ("no" == target[i]){
            negativeCount++;
        }
    }
    //calculate the entropy for the entire set
    float positiveE = pi(positiveCount, subSet);
    float negativeE = pi(8, subSet);
    float setEntropy = calcEntropy(positiveE, negativeE);
    cout << "Entropy of set is " << setEntropy << endl;

    //Count of members with particular attribute
    //Count of corresponding members with 'positive'
    //tally corresponding negative members
    float tallEntropy, shortEntropy;

    
    tallEntropy = attributeEntropy(positiveCount, negativeCount, subSet);
    //parameters(posWithAttribute, negWithAttribute, totalSampleSize)
    cout << "Tall entropy is: " << tallEntropy << endl;


    //TODO: repeat above process - turn this into function for single feature
    shortEntropy = attributeEntropy(1, 5, 10);
    cout << "The entropy for short is: " << shortEntropy << endl;



    //Calculating information gain
    float gain;
    gain = infoGain(setEntropy, tallEntropy, shortEntropy);
    cout << "Gain for height is: " << gain << endl;

    return 0;

}

