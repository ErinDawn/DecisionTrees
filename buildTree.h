#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"

using namespace std;


#ifndef BUILDTREE_H
#define BUILDTREE_H


void buildTree(Node*& root, DataStruct inData);

DataStruct openFromFile(string fileName, int n_features, int n_samples);



#endif //BUILDTREE_H
