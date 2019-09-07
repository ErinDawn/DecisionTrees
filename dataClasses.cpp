#include <vector>
#include <string>
#include <iostream>
#include "dataClasses.h"

using namespace std;


Node::Node(string name){
	name = name;
};

Node* Node::goToNode(int index){
	return attributes[index];
};

void Node::createExtension(string attributeReference){
	Node* extension;
	extension = new Node(attributeReference);
	attributes.push_back(extension);
};