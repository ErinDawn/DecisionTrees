#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "dataClasses.h"

using namespace std;


Node::Node(int value, bool isClass){	//if classifier is true, resulting class node
	feature = value;
	classifier = isClass;
	nextPtr.resize(5, nullptr);
};

Node* Node::goToNode(int index){
	switch (index){
		case 0:
			return nextPtr[0];
			break;
		case 1:
			return nextPtr[1];
			break;
		case 2:
			return nextPtr[2];
			break;
		case 3:
			return nextPtr[3];
			break;
		case 4:
			return nextPtr[4];
			break;
		default:
			return nullptr;
			break;
	}

};

bool Node::isClass(){
	return classifier;
};

int Node::getFeature(){
	return feature;
};

void Node::setClassifier(bool classifier){
	classifier = classifier;
};

bool Node::getClassifier(){
	return classifier;
};

Node* Node::getNextNode(int next){
	Node* temp;
	temp = nextPtr[next];
	return temp;
}

void Node::testNode(){
	cout << "-Node details-" << endl;
	cout << "feature = " << feature << endl;
	cout << "classifier = " << classifier << endl;
	cout << "nextPtr holds 5 pointers with the following values:" << endl;
	for (int i = 0; i < 5; i++){
		if (nextPtr[i] == nullptr){
			cout << "nullptr" << endl;
		} else {
			cout << "Value " << nextPtr[i] << " referenced at " << i << endl;
		}

	}
};