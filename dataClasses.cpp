#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "dataClasses.h"

using namespace std;


Node::Node(){
	feature = 999;
	classifier = true;
	ptrList.resize(5, nullptr);
};

Node::Node(int value, bool isClass){	//if classifier is true: is class node, if false: feature
	feature = value;
	classifier = isClass;
	ptrList.resize(5, nullptr);
};


bool Node::isClass(){
	return classifier;
};

int Node::getFeature(){
	return feature;
};

void Node::setFeature(int feat){
	feature = feat;
};

void Node::setClassifier(bool classifier){
	classifier = classifier;
};

bool Node::getClassifier(){
	return classifier;
};