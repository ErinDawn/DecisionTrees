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
string fileName;

cout << "Please enter the file name of the data set:" << endl;
getline(cin, fileName);

newTable = translator();

//translate(newTable, "iris.data");	
//translate(newTable, "example.txt");	//contrived example
translate(newTable, fileName);

DataStruct newData;
int n_features = newTable.n_features;
int n_samples = newTable.n_samples;
int n_classes = newTable.n_classes;

newData = openFromFile("newdata.txt", n_features, n_samples, n_classes);
newData.expandedList.clear();
newData.remaining_features = n_features;    //n_features will have to be added in

cout << "************************************************" << endl;
Node* rootNode;
rootNode = new Node();
cout << "building tree..." << endl;
buildTree(rootNode, newData);
cout << "************************************************" << endl;
Node* tree;
tree = rootNode;
cout << "Printing tree ..." << endl;
printTree(rootNode, "", newTable);


cout << "************************************************" << endl;
cout << "testing each sample against tree...." << endl;
testTree(newData, newTable, rootNode);

cout << "************************************************" << endl;
cout << "Printing the reference table..." << endl;
cout << "************************************************" << endl;
newTable.printTable();


return 0;
}

