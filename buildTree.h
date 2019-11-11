#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <tuple>
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"

using namespace std;


#ifndef BUILDTREE_H
#define BUILDTREE_H


void buildTree(Node*& root, DataStruct inData);

DataStruct openFromFile(string fileName, int n_features, int n_samples, int n_classes);

int runTree(vector<int> singleItem, Node* tree, ReferenceTable table);

void printTree(Node* tree, string branch, ReferenceTable table);

void testTree(DataStruct inData, ReferenceTable table, Node* tree);


#endif //BUILDTREE_H
