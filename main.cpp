#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "buildTree.h"
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"

using namespace std;



int main() {

     DataStruct newData;
     int n_features = 3;
     int n_samples = 10;
     newData = openFromFile("test.txt", n_features, n_samples);
     newData.expandedList.clear();
     newData.remaining_features = n_features;    //n_features will have to be added in
     cout << "************************************************" << endl;


// //pass inData into buildTree function

Node rootNode = buildTree(newData);
rootNode.testNode();

Node* tree;
tree = &rootNode;

//Use tree to classify a new data item
//i.e.

return 0;
}

