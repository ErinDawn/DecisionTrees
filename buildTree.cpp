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
    int classCounts[n_classes];     //the number of samples of each class
    int featureCount[n_features][5];    //i.e number of samples with feature F
    int featureClassCount2[n_features][5][n_classes];
    float featureEntropy[n_features][5];    //the entropy of each attribute

    //set all counts to zero
    for (int i = 0; i < n_features; i++){
        for (int j = 0; j < 5; j++){
            featureCount[i][j] = 0; 
            featureEntropy[i][j] = 0.0;
            for (int k = 0; k < n_classes; k++){
                featureClassCount2[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < n_classes; i++){
        classCounts[i] = 0;
    }

    //calculate the class counts for the set
    for (int i = 0; i < n_samples; i++){    //iterate through dataset, count no. of samples of each class
        int temp = inData.sampleC[i];
        for (int j = 0; j < n_classes; j++){
            if (temp == j){
                classCounts[j]++;
            }
        }
    }

    //Possibility 1 - all samples are of the same class
    for (int i = 0; i < n_classes; i++){    //If all samples are of a particular class, return that class
        if (classCounts[i] == n_samples){
            Node* leaf;
            leaf = new Node(i, true);
            root = leaf;
            return;
        }
    }

    //Possibility 2 - no features remain to be assessed
    if (inData.remaining_features == 0){    //If no features remain to be assessed
        //Return a single node with the most common class for this branch
        int maxCount = 0;
        index = 0;
        for (int i = 0; i < n_classes; i++){
            if (classCounts[i] > maxCount){
                index = i;
                maxCount = classCounts[i];
            }
        }
        Node* leaf;
        leaf = new Node(index, true);
        root = leaf;
        return;
    }

    //Else, calculate the node with the highest info gain
    //create a subNode for each value of that feature
    for (int i = 0; i< n_samples; i++){  //look at each sample
        for (int j = 0; j < n_features; j++){   //for every feature, get the attribute
            if (!inData.alreadyExpanded(j)){
                int attr = inData.sampleF[i][j];    //sample i and feature j has value attr
                int classWithA = inData.sampleC[i]; //sample i has class classWithA
                featureClassCount2[j][attr][classWithA]++;
                featureCount[j][attr]++;    //for feature j with attribute attr, add 1 to count
            }
        }
    }

    int posCount, subSampleSize;
    int attributeCount = 0;
    int classCountWAttribute = 0;
    float tempResult;
    float piResult = 0.0, entropyResult =0.0, entropySum = 0.0;
    //calc the entropy for each feature value with a count
    for (int i = 0; i< n_features; i++){    //for each feature
        for (int j = 0; j < 5; j++){    //for each attribute
            if (featureCount[i][j] <1) {
                featureEntropy[i][j] = 0.0;
                entropySum = 0.0;
                break;
            }
            attributeCount = featureCount[i][j];    //number of samples with this attribute.
            //for each class - get the total number of counts with this attribute
            for (int k = 0; k < n_classes; k++){
                posCount = featureClassCount2[i][j][k]; //number of samples which are this class
                if (posCount == 0){
                    entropyResult = 0;
                } else {
                    piResult = pi(posCount, attributeCount);
                    entropyResult = calcEntropy(piResult);
                }
                entropySum = entropySum + entropyResult;
            }
            //once entropy for each class is done - we have entropy for that ATTRIBUTE
            entropySum = entropySum * (pi(attributeCount, n_samples));
            featureEntropy[i][j] = entropySum;
            entropySum = 0.0;
        }
    }

    float setEntropy = 0.0;
    float piTemp = 0.0;
    for (int i = 0; i< n_classes; i++){
        posCount = classCounts[i];
        piTemp = pi(posCount, n_samples);
        piTemp = calcEntropy(piTemp);
        setEntropy = setEntropy + piTemp;
    }
    cout << "Entropy of set is " << setEntropy << endl;

    //Calculating information gain and selecting the highest gain from array of gains
    float gain[n_features];
    float highestGain = 0;
    int highestGainIndex;

    for (int i = 0; i < n_features; i++){
        gain[i] = calcInfoGain(setEntropy, featureEntropy[i][0], featureEntropy[i][1],
                        featureEntropy[i][2], featureEntropy[i][3], featureEntropy[i][4]);
        if (gain[i] > highestGain){
            if (!inData.alreadyExpanded(i)) {//if attribute index has not already been evaluated
                highestGain = gain[i];
                highestGainIndex = i;
            }
        }
        cout << "Information gain for feature " << i << " = " << gain[i] << endl;
    }

    //select largest info gain
    cout << "***************************************************" << endl;
    cout << "The highest gain is index " << highestGainIndex;
    cout << " with a gain of: " << highestGain << endl;
    cout << "***************************************************" << endl;


    if (highestGain <= 0){  //if there is nothing to learn from remaining features
        //select the most common class from subSample
        //Return a single node with the label = most common value for this branch
        int maxCount = 0;
        index = 0;
        for (int i = 0; i < n_classes; i++){
            if (classCounts[i] > maxCount){
                index = i;
                maxCount = classCounts[i];
            }
        }
        //return a leaf with the largest class count
        Node* leaf;
        leaf = new Node(index, true);
        root = leaf;
        return;
    }

    //create a node for each feature value
    //add all items with that value to the nodes feature and class arrays
    Node* leaf;
    leaf = new Node(highestGainIndex, false);
    root = leaf;
    DataStruct subList;
    subList.n_features = n_features;
    subList.n_classes = n_classes;

    //For feature 'highestGainIndex'
    for (int j = 0; j < 5; j++){    //with values 1-5
        subList.n_samples = featureCount[highestGainIndex][j];  //each subList will have a different number of samples
        //Create a sublist for each value of feature[highestGainIndex]
        subList.v.clear();
        subList.sampleF.clear();
        subList.sampleC.clear();
        subList.expandedList.clear();
        subList.expandedList = inData.expandedList;

        if(featureCount[highestGainIndex][j] > 0){  //if a featureCount[highestGainIndex][j] has any items
            for (int itemIndex = 0; itemIndex < n_samples; itemIndex++){  //iterate through all samples
                if (inData.sampleF[itemIndex][highestGainIndex] == j){  //any item with feature value matching
                     // gets pushed to the back of the subList
                    subList.sampleF.push_back(inData.sampleF[itemIndex]);
                    subList.sampleC.push_back(inData.sampleC[itemIndex]);
                }
            }
            //DEBUGGING ****print the matrix for this batch of feature values
            //subList.printMatrix();
            subList.expandedList.push_back(highestGainIndex);
            subList.remaining_features = inData.remaining_features-1;
            Node* leaf;
            buildTree(leaf, subList);
            root->ptrList[j] = leaf;
        } else {
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
    //cout << "runTree entered " << endl;
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
        return feature;
    } else {
        //if the node isn't a class, and isn't null, expand feature node.
        current = current->ptrList[nextIndex];
        result = runTree(singleItem, current, table);
        return result;
    }
};


void printTree(Node* tree, string branch, ReferenceTable table){
    //branch should start empty
    Node* current;
    current = tree;
    bool isClass = current->getClassifier();
    int feature = current->getFeature();
    if (!isClass){
        cout << " feature " << feature;
        cout << " - " << table.featureNames[feature] << " " << endl;
        branch = branch + "--------";
        for (int i = 0; i < 5; i++){
            Node* next = tree->ptrList[i];
            if (next != nullptr){
                cout << branch << " option " << i << " returns ";
                printTree(next, branch, table);
            }
        }
    }
    
    if (isClass){
        cout << "class " << feature;
        cout << " - " << table.classList[feature] << endl;
    }
};

void testTree(DataStruct inData, ReferenceTable table, Node* tree){
    //calls run tree on each dataSample
    //compares result to the associated class in inData
    //prints success or fail for each item
    //based upon if tree has classified this correctly
    int n_samples = inData.n_samples;
    int expectedClass;
    int result;
    int successCount = 0;
    int failCount = 0;
    vector<int>sample;
    for (int i  = 0; i < n_samples; i++){
        sample = inData.sampleF[i];
        expectedClass = inData.sampleC[i];
        result = runTree(sample, tree, table);
        if(expectedClass == result){
            successCount++;
        } else {
            failCount++;
        }
    }
    cout << "Total successful classifications = " << successCount << endl;
    cout << "Total failed classifications = " << failCount << endl;
};