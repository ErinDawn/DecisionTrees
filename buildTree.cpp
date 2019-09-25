#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"
#include "buildTree.h"

using namespace std;



/*
NOTE****** The following assumptions have been made:
	* the number of features and number of samples are being supplied
	* the samples incl. features and classes are in int format
    * there are a maximum of 5 different values for each feature
*/
void buildTree(Node*& root, DataStruct inData){
	////////////////////////////////////////////////////////////////////////////////////////////////
    int n_features = inData.n_features;
	int n_samples = inData.n_samples;
    int index = 0;

	//calc the entropy of set.
    int positiveCount = 0;
    int negativeCount = 0;
    int temp;
    int featureCount[n_features][5];
    int featurePosCount[n_features][5];
    float featureEntropy[n_features][5];

    //set all counts to zero
    for (int i = 0; i < n_features; i++){
        for (int j = 0; j < 5; j++){
            featureCount[i][j] = 0;
            featurePosCount[i][j] = 0;
        }
    }

    //Calculate the positive and negative members of the set
    for (int i = 0; i < n_samples; i++){
        temp = inData.sampleC[i];
        switch(temp){
            case 1:
                positiveCount++;
                break;
            case 0:
                negativeCount++;
                break;
        }
    }
    if (positiveCount == n_samples){
        // Return a leaf node with + label
        //cout << "return pos class" << endl;
        Node* leaf;
        leaf = new Node(1, true);
        root = leaf;
        return;
    }
    if (negativeCount == n_samples){
        //Return a leaf node with - label
        //cout << "return neg class" << endl;
        Node* leaf;
        leaf = new Node(0, true);
        root = leaf;
        return;
    }
    if (inData.remaining_features == 0){
        //cout << "No features remain" << endl;
        //Return a single node with the label = most common value for this branch
        if (positiveCount >= negativeCount){
            //return a leaf with + label
            //cout << "return pos class" << endl;
            Node* leaf;
            leaf = new Node(1, true);
            root = leaf;
            return;
        } else {
            //return a leaf with - label
            //cout << "return neg class" << endl;
            Node* leaf;
            leaf = new Node(0, true);
            root = leaf;
            return;
        }
    }
    ////////////////////////////////////////////////////////////////////////////
    ///////Else, calculate the node with the highest info gain//////////////////
    ////////////create a subNode for each value of that feature/////////////////
    cout << "*********************************************************" << endl;


    //Calculate the number of values for each feature.
    for (int i = 0; i < n_samples; i++){
        for (int j = 0; j < n_features; j++){
            if (!inData.alreadyExpanded(j)){ //if feature at index j has not yet been expanded

                //use temp to get value at inData.sampleF[sampleNumber][featureNumber]
                temp = inData.sampleF[i][j]; 
                switch (temp){  //add one to the applicable feature value
                    case 0:
                        featureCount[j][0]++;
                        //if corresponding class is positive, add on to the featurePosCount
                        if (inData.sampleC[i] == 1){
                            featurePosCount[j][0]++;
                        }
                        break;
                    case 1:
                        featureCount[j][1]++;
                        if (inData.sampleC[i] == 1){
                            featurePosCount[j][1]++;
                        }
                        break;
                    case 2:
                        featureCount[j][2]++;
                        if (inData.sampleC[i] == 1){
                            featurePosCount[j][2]++;
                        }
                        break;
                    case 3:
                        featureCount[j][3]++;
                        if (inData.sampleC[i] == 1){
                            featurePosCount[j][3]++;
                        }
                        break;
                    case 4:
                        featureCount[j][4]++;
                        if (inData.sampleC[i] == 1){
                            featurePosCount[j][4]++;
                        }
                        break;
                    default:
                        break;
                }
            } 
            
        }
    }

    //calc the entropy for each feature value with a count
    int featureNegCount;
    for (int i = 0; i < n_features; i++){
        for (int j = 0; j < 5; j++){
            if (featureCount[i][j] <1) {break;}  // if (featureCount[i][j] == -1) {break;}  //why was this neg 0??
            featureNegCount = featureCount[i][j] - featurePosCount[i][j];
            featureEntropy[i][j] = attributeEntropy(featurePosCount[i][j], featureNegCount, n_samples);
        }
    }
    cout << "*************************************************" << endl;
    
    //calculate the entropy for the entire set
    float positiveE = pi(positiveCount, n_samples);
    float negativeE = pi(negativeCount, n_samples);
    float setEntropy = calcEntropy(positiveE, negativeE);
    cout << "Entropy of set is " << setEntropy << endl;

    //Calculating information gain and selecting the highest gain from array of gains
    float gain[n_features];
    float highestGain = 0;
    int highestGainIndex;

    for (int i = 0; i < n_features; i++){
        gain[i] = calcInfoGain(setEntropy, featureEntropy[i][0], featureEntropy[i][1],
                        featureEntropy[i][2], featureEntropy[i][3], featureEntropy[i][4]);
        if (gain[i] > highestGain){
            highestGain = gain[i];
            highestGainIndex = i;
        }
    }
    //select largest info gain
    cout << "The highest gain is index " << highestGainIndex;
    if (highestGainIndex == 0){
        cout << " - height - ";
    }
    if (highestGainIndex == 1){
        cout << " - dexterity - ";
    }
    if (highestGainIndex == 2){
        cout << " - fitness - ";
    }
    cout << " with a gain of: " << highestGain << endl;
    cout << "***************************************************" << endl;


    if (highestGain == 0){
        //if info gain = 0, select the most common class from subSample
        cout << "Location: highest gain = 0" << endl;
        cout << "Returning root..." << endl;
         if (positiveCount > negativeCount){
            Node* leaf;
            leaf = new Node(1, true);
            root = leaf;
            return;
        } else {
            Node* leaf;
            leaf = new Node(0, true);
            root = leaf;
            return;
        }
    }
        

    //************************************************************
    //create a node for each feature value
    //add all items with that value to the nodes feature and class arrays

    Node* leaf;
    leaf = new Node(highestGainIndex, false);
    root = leaf;
    DataStruct subList;
    subList.n_features = n_features;

    //For feature 'highestGainIndex'
    for (int j = 0; j < 5; j++){    //with values 1-5
    	subList.n_samples = featureCount[highestGainIndex][j];	//each subList will have a different number of samples
        //Create a sublist for each value of feature[highestGainIndex]
        subList.v.clear();
        subList.sampleF.clear();
        subList.sampleC.clear();

    	if(featureCount[highestGainIndex][j] > 0){	//if a featureCount[highestGainIndex][j] has any items
    		for (int itemIndex = 0; itemIndex < n_samples; itemIndex++){  //iterate through all samples
    			if (inData.sampleF[itemIndex][highestGainIndex] == j){  //any item with feature value matching
    			     // gets pushed to the back of the subList

    				subList.sampleF.push_back(inData.sampleF[itemIndex]);
    				subList.sampleC.push_back(inData.sampleC[itemIndex]);
    			}
    		}
            //DEBUGGING ****print the matrix for this batch of feature values
   			subList.printMatrix();
    	}
        subList.expandedList.push_back(highestGainIndex);
        subList.remaining_features = inData.remaining_features-1;
        Node* leaf;
        buildTree(leaf, subList);
        root->ptrList[j] = leaf;
    }
};




DataStruct openFromFile(string fileName, int n_features, int n_samples){
	DataStruct inData;
	inData.n_features = n_features;
	inData.n_samples = n_samples;
 	inData.v.resize(5, -1);
 	inData.sampleF.resize(n_samples, inData.v);
 	inData.sampleC.resize(n_samples, -1);

	ifstream in(fileName);
    string inString;
    int index = 0;

    //Read data in from file
    if(!in){
        cout << "Error: Cannot open input file." << endl;
        exit(1);
    }
    while (getline(in, inString)){  //populate the dataArray and target array
        int length = inString.length();
        size_t pos = 0;
        string token;
        int j = 0;
        while ((pos = inString.find(",")) != string::npos) {    //take each feature value from the string
            token = inString.substr(0, pos);
            trim(token);
            stringstream item;
            item << token;
            item >> inData.sampleF[index][j];
            inString.erase(0, pos + 1);
            j++;
        }
        trim(inString); //last item in the string will be the class
        stringstream classItem;
        classItem << inString;
        classItem >> inData.sampleC[index];
        index++;
        
    }
    cout << endl << endl;
    inData.printMatrix();
    return inData;

};