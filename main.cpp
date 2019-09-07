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

    int featureList[n_features][5];     //set an array with feature row, value column
    //set all values at -1 to begin - this denotes no feature value
    for (int i = 0; i < n_features; i++){
        for (int j = 0; j < 5; j++){
            featureList[i][j] = -1;
            cout << "Feature " << i << " with vale index " << j << " is set to -1" << endl;
        }
    }

    featureList[0][0] = 0;  //height, tall
    featureList[0][1] = 1;  //height, short
    featureList[1][0] = 0;  //dexterity, good
    featureList[1][1] = 1;  //dexterity, bad


    string classList[n_classes];
    classList[0] = "yes";
    classList[1] = "no";
    //*******************************************************************************

    int dataArray[n_samples][n_features];
    int target[n_samples];
    
    //Refactor below - Load data in using function***********************************
    //read in the data to each corresponding place in the arrays

    //tall = 0, short = 1   Height = dataArray[X][0]    total 4 tall, total 6 short
    //good = 0, bad = 1     Dexterity = [X][1]          total 4 good, total 6 bad
    dataArray[0][0] = 0;    // tall
    dataArray[0][1] = 0;    // good
    dataArray[1][0] = 1;        //short
    dataArray[1][1] = 1;        //bad
    dataArray[2][0] = 0;    //tall
    dataArray[2][1] = 1;    //bad
    dataArray[3][0] = 1;        //short
    dataArray[3][1] = 1;        //bad
    dataArray[4][0] = 0;    //tall
    dataArray[4][1] = 0;    //good
    dataArray[5][0] = 1;        //short
    dataArray[5][1] = 0;        //good
    dataArray[6][0] = 0;    //tall
    dataArray[6][1] = 1;    //bad
    dataArray[7][0] = 1;        //short
    dataArray[7][1] = 1;        //bad
    dataArray[8][0] = 1;    //short
    dataArray[8][1] = 0;    //good
    dataArray[9][0] = 1;        //short
    dataArray[9][1] = 1;        //bad

    //"yes" = 1                                         total 2 yes
    //"no" = 0                                          total 8 no
    target[0] = 1;  //tall, good, yes
    target[1] = 0;
    target[2] = 0;
    target[3] = 0;
    target[4] = 0;
    target[5] = 0;
    target[6] = 0;
    target[7] = 0;
    target[8] = 1;  //short, good, yes
    target[9] = 0;

    //Refactor above**********************************************************

    //calc the entropy of set.
    int positiveCount = 0;
    int negativeCount = 0;
    int subSet = n_samples;
    int temp;
    int featureCount[n_features][5];
    int featurePosCount[n_features][5];
    float featureEntropy[n_features][5];

    //set all counts to zero to begin
    for (int i = 0; i < n_features; i++){
        for (int j = 0; j < 5; j++){
            featureCount[i][j] = 0;
            featurePosCount[i][j] = 0;
        }
    }

    //Calculate the positive and negative members of the set
    for (int i = 0; i < subSet; i++){
        temp = target[i];
        switch(temp){
            case 1:
                positiveCount++;
            case 0:
                negativeCount++;
        }
    }
    //Calculate the number of values for each feature.
    for (int i = 0; i < subSet; i++){
        for (int j = 0; j < n_features; j++){
            //use temp to get value at dataarray[sampleNumber][featureNumber]
            temp = dataArray[i][j]; 
            switch (temp){  //add one to the applicable feature value
                case 0:
                    featureCount[j][0]++;
                    //if corresponding class is positive, add on to the featurePosCount
                    if (target[i] == 1){
                        featurePosCount[j][0]++;
                    }
                    break;
                case 1:
                    featureCount[j][1]++;
                    if (target[i] == 1){
                        featurePosCount[j][1]++;
                    }
                    break;
                case 2:
                    featureCount[j][2]++;
                    if (target[i] == 1){
                        featurePosCount[j][2]++;
                    }
                    break;
                case 3:
                    featureCount[j][3]++;
                    if (target[i] == 1){
                        featurePosCount[j][3]++;
                    }
                    break;
                case 4:
                    featureCount[j][4]++;
                    if (target[i] == 1){
                        featurePosCount[j][4]++;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    cout << "The counts using array and loop are: " << endl;
    //calc the entropy for each feature value with a count
    int featureNegCount;
    subSet = 10;
    for (int i = 0; i < n_features; i++){
        for (int j = 0; j < 5; j++){
            if (featureCount[i][j] <1) {break;}  // if (featureCount[i][j] == -1) {break;}  //why was this neg 0??
            featureNegCount = featureCount[i][j] - featurePosCount[i][j];
            featureEntropy[i][j] = attributeEntropy(featurePosCount[i][j], featureNegCount, subSet);
        }
    }
    cout << "*************************************************" << endl;
    cout << "*************************************************" << endl;
    cout << endl << endl;
    
    //calculate the entropy for the entire set
    float positiveE = pi(positiveCount, subSet);
    float negativeE = pi(8, subSet);
    float setEntropy = calcEntropy(positiveE, negativeE);
    cout << "Entropy of set is " << setEntropy << endl;

    //Calculating information gain
    float gain[n_features];
    for (int i = 0; i < n_features; i++){
        gain[i] = calcInfoGain(setEntropy, featureEntropy[i][0], featureEntropy[i][1],
                        featureEntropy[i][2], featureEntropy[i][3], featureEntropy[i][4]);
    }
    cout << "Gain for height is: " << gain[0] << endl;
    return 0;
}

