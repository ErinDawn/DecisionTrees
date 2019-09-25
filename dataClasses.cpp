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

Node::Node(int value, bool isClass){	//if classifier is true, resulting class node
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


void Node::testNode(){
	cout << "-Node details-" << endl;
	cout << "feature = " << feature << endl;
	cout << "classifier = " << classifier << endl;
	cout << "ptrList holds 5 pointers with the following values:" << endl;
	for (int i = 0; i < 5; i++){
		if (ptrList[i] == nullptr){
			cout << "nullptr" << endl;
		} else {
			cout << "Value " << ptrList[i] << " referenced at " << i << endl;
		}

	}
};