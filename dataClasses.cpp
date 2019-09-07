#include <vector>
#include <string>
#include <iostream>
#include "dataClasses.h"

using namespace std;


Node::Node(int feature, bool classifier){	//if classifier is true, resulting class node
	feature = feature;
	classifier = classifier;
};

Node* Node::goToNode(int index){
	return value[index];
};

void Node::createExtension(int valueReference, bool classifier){
	Node* extension;
	extension = new Node(valueReference, classifier);
	value.push_back(extension);
};

bool Node::isClass(){
	return classifier;
};