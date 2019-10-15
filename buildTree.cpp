#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"
#include "buildTree.h"

using namespace std;

float roundFloat(float var) 
{
    var = (var*100);
    int temp = var;
    var = temp * 1.0;
    var = var / 100;
    return var; 
}


/*
NOTE****** The following assumptions have been made:
	* the number of features and number of samples are being supplied
	* the samples incl. features and classes are in int format
    * there are a maximum of 5 different values for each feature
*/
void buildTree(Node*& root, DataStruct inData){
    int n_features = inData.n_features;
	int n_samples = inData.n_samples;
    int n_classes = inData.n_classes;
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
    //if all items are of one particular class
    //return a class node of that value
    if (positiveCount == n_samples){
        // Return a leaf node with + label
        cout << "return pos class" << endl;
        Node* leaf;
        leaf = new Node(1, true);
        root = leaf;
        return;
    }
    if (negativeCount == n_samples){
        //Return a leaf node with - label
        cout << "return neg class" << endl;
        Node* leaf;
        leaf = new Node(0, true);
        root = leaf;
        return;
    }
    //if all features have been assessed
    //Return a class node with most common value
    if (inData.remaining_features == 0){
        cout << "No features remain" << endl;
        if (positiveCount >= negativeCount){
            //return a leaf with + label
            cout << "return pos class" << endl;
            Node* leaf;
            leaf = new Node(1, true);
            root = leaf;
            return;
        } else {
            //return a leaf with - label
            cout << "return neg class" << endl;
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
            if (featureCount[i][j] <1) {break;} 
            featureNegCount = featureCount[i][j] - featurePosCount[i][j];
            featureEntropy[i][j] = attributeEntropy(featurePosCount[i][j], featureNegCount, n_samples);
            featureEntropy[i][j] = roundFloat(featureEntropy[i][j]);
        }
    }
    cout << "*************************************************" << endl;
    
    //calculate the entropy for the entire set
    float positiveE = pi(positiveCount, n_samples);
    float negativeE = pi(negativeCount, n_samples);
    float setEntropy = calcEntropy(positiveE, negativeE);
    setEntropy = roundFloat(setEntropy);
    cout << "Entropy of set is " << setEntropy << endl;

    //Calculating information gain and selecting the highest gain from array of gains
    float gain[n_features];
    float highestGain = 0;
    int highestGainIndex;

    for (int i = 0; i < n_features; i++){
        gain[i] = calcInfoGain(setEntropy, featureEntropy[i][0], featureEntropy[i][1],
                        featureEntropy[i][2], featureEntropy[i][3], featureEntropy[i][4]);
        gain[i] = roundFloat(gain[i]);
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


    if (highestGain <= 0){  //if there is nothing to learn from remaining features
        //select the most common class from subSample
        cout << "Highest gain = " << highestGain << endl;
        cout << "Returning the most common class from subSample" << endl;

        cout << "Returning root..." << endl;
         if (positiveCount >= negativeCount){
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
    cout << "Creating a node for all feature values..." << endl;
    Node* leaf;
    leaf = new Node(highestGainIndex, false);
    root = leaf;
    DataStruct subList;
    subList.n_features = n_features;

    //For feature 'highestGainIndex'
    for (int j = 0; j < 5; j++){    //with values 1-5
        cout << "Feature " << highestGainIndex << " with value " << j << ".....";
        subList.n_samples = featureCount[highestGainIndex][j];  //each subList will have a different number of samples
        //Create a sublist for each value of feature[highestGainIndex]
        subList.v.clear();
        subList.sampleF.clear();
        subList.sampleC.clear();

        if(featureCount[highestGainIndex][j] > 0){  //if a featureCount[highestGainIndex][j] has any items
            for (int itemIndex = 0; itemIndex < n_samples; itemIndex++){  //iterate through all samples
                if (inData.sampleF[itemIndex][highestGainIndex] == j){  //any item with feature value matching
                     // gets pushed to the back of the subList
                    subList.sampleF.push_back(inData.sampleF[itemIndex]);
                    subList.sampleC.push_back(inData.sampleC[itemIndex]);
                }
            }
            //DEBUGGING ****print the matrix for this batch of feature values
            subList.printMatrix();
            subList.expandedList.push_back(highestGainIndex);
            subList.remaining_features = inData.remaining_features-1;
            Node* leaf;
            cout << "Creating new node" << endl;
            buildTree(leaf, subList);
            root->ptrList[j] = leaf;
        } else {
            cout << "Creating null ptr" << endl;
            root->ptrList[j] = nullptr;
        }
    }
};




DataStruct openFromFile(string fileName, int n_features, int n_samples, int n_classes){
	DataStruct inData;
	inData.n_features = n_features;
	inData.n_samples = n_samples;
    inData.n_classes = n_classes;
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


int runTree(vector<int> singleItem, Node* tree, ReferenceTable table){
    Node* current;
    current = tree;
    bool isClass = current->getClassifier();
    int feature = current->getFeature();
    int nextIndex = singleItem[feature];
    int result;

    if (current == nullptr){
        cout << "Empty tree" << endl;
        return -999;
    }
    if (isClass){
        //if node is a class, return the class
        cout << "Class found, returning "<< feature << endl;
        cout << "Class found, returning "<< table.classList[feature] << " " << feature << endl;
        return feature;
    } else {
        cout << "Assessing feature: " << feature;
        cout << " " << table.featureNames[feature] << " " << endl;
        //if the node isn't a class, and isn't null, assess the feature.
        current = current->ptrList[nextIndex];
        cout << "calling runTree on next pointer" << endl;
        result = runTree(singleItem, current, table);
        return result;
    }
};

//refactor for use with a reference list - to make data agnostic
void printTree(Node* tree, string branch, ReferenceTable table){
    //branch should start empty
    Node* current;
    current = tree;
    bool isClass = current->getClassifier();
    int feature = current->getFeature();
    if (!isClass){
        cout << " Feature " << feature;
        cout << " " << table.featureNames[feature] << " " << endl;
        branch = branch + "--------";
        for (int i = 0; i < 5; i++){
            //if nextPtr is not null
            Node* next = tree->ptrList[i];
            if (next != nullptr){
                cout << branch << " option " << i << " ";
                printTree(next, branch, table);
            }
        }
    }
    
    if (isClass){
        cout << "Class " << feature;
        cout << " " << table.classList[feature] << " " << endl;
    }
};

