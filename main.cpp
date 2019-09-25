#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include "buildTree.h"
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"

using namespace std;

int runTree(vector<int> singleItem, Node* tree){
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
        return feature;
    } else {
        cout << "Assessing feature: " << feature;
        if (feature == 0){ cout << " height " << endl;}
        if (feature == 1){ cout << " dexterity " << endl;}
        if (feature == 2){ cout << " fitness " << endl;}
        //if the node isn't a class, and isn't null, assess the feature.
        current = current->ptrList[nextIndex];
        cout << "calling runTree on next pointer" << endl;
        result = runTree(singleItem, current);
        return result;
    }
};



int main() {

DataStruct newData;
int n_features = 3;
int n_samples = 10;
newData = openFromFile("test.txt", n_features, n_samples);
newData.expandedList.clear();
newData.remaining_features = n_features;    //n_features will have to be added in
cout << "************************************************" << endl;

//pass inData into buildTree function

Node* rootNode;
rootNode = new Node();
buildTree(rootNode, newData);
cout << "************************************************" << endl;

Node* tree;
tree = rootNode;

//Use tree to classify a new data item
//i.e. an expected 0 value
cout << "creating test vector" << endl;
vector<int> dataItem(2, 0);
dataItem.push_back(2);
int temp1, temp2, temp3;

cout << "Test vector set to 0, 0, 2" << endl;
temp1 = dataItem[0];
temp2 = dataItem[1];
temp3 =  dataItem[2];
cout << temp1 << ", " << temp2 << ", " << temp3 << endl;
cout << "Expected class = 0 - Not professional" << endl;

int finalClass;
cout << "************************************************" << endl;
cout << "Running tree" << endl;\
finalClass = runTree(dataItem, tree);
cout  << "Class returned = " << finalClass << endl;


//i.e. an expected 1 value
cout << "Test vector set to 1, 0, 2" << endl;
dataItem[0] = 1;
dataItem[1] = 0;
dataItem[2] = 2;

temp1 = dataItem[0];
temp2 = dataItem[1];
temp3 =  dataItem[2];
cout << temp1 << ", " << temp2 << ", " << temp3 << endl;
cout << "Expected class = 1 - Professional" << endl;

cout << "************************************************" << endl;
cout << "Running tree" << endl;
finalClass = runTree(dataItem, tree);
cout  << "Class returned = " << finalClass << endl;
cout << "************************************************" << endl;


return 0;
}

