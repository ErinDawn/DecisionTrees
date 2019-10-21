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
#include "translate.h"

using namespace std;



int main() {


ReferenceTable newTable;
newTable = translator();
newTable.printTable();

//translate(newTable, "example.txt");	//full string data
translate(newTable, "test.txt");	//full string data
cout << "translate file using table successful" << endl;


DataStruct newData;
int n_features = newTable.n_features;
int n_samples = newTable.n_samples;
int n_classes = newTable.n_classes;

newData = openFromFile("newdata.txt", n_features, n_samples, n_classes);
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
cout << "Printing tree ..." << endl;
printTree(rootNode, "", newTable);

//Use tree to classify a new data item
//i.e. an expected 0 value
cout << "creating test vector" << endl;
vector<int> dataItem(3, 1);
int temp1, temp2, temp3;

cout << "Test vector set to 1, 1, 1" << endl;
temp1 = dataItem[0];
temp2 = dataItem[1];
temp3 = dataItem[2];
cout << temp1 << ", " << temp2 << ", " << temp3 << endl;
cout << "Expected class = 0 - Not professional" << endl;

int finalClass;
cout << "************************************************" << endl;
cout << "Running tree" << endl;\
finalClass = runTree(dataItem, tree, newTable);
cout  << "Class returned = " << finalClass << endl;
cout << endl << "************************************************" << endl;


//i.e. an expected 1 value
cout << "Test vector set to 1, 0, 0" << endl;
dataItem[0] = 1;
dataItem[1] = 0;
dataItem[2] = 0;

temp1 = dataItem[0];
temp2 = dataItem[1];
temp2 = dataItem[2];
cout << temp1 << ", " << temp2 << endl;
cout << "Expected class = 1 - Professional" << endl;

cout << "************************************************" << endl;
cout << "Running tree" << endl;
finalClass = runTree(dataItem, tree, newTable);
cout  << "Class returned = " << finalClass << endl;
cout << "************************************************" << endl;
cout << "************************************************" << endl;


printTree(tree, "", newTable);
newTable.printTable();


return 0;
}

