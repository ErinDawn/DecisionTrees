#ifndef DATACLASS_H
#define DATACLASS_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

//Make entropy a member? Or keep separate? If data changes, entropy changes... but so does member count etc.
class Node{
private:
	string name;
	vector<Node *> attributes;	//a list of node pointers, accessed according to attribute


public:
	Node();
	Node(string name);
	Node* goToNode(int index);	//go to the node pointer at index
	void createExtension(string attributeReference);	//can use just an int to refer
};

#endif //DATACLASS_H