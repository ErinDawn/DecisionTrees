#ifndef DATACLASS_H
#define DATACLASS_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

//Make entropy a member? Or keep separate? If data changes, entropy changes... but so does member count etc.
class Node{
private:
	int feature;
	bool classifier;	//if classifier is true, resulting class node
	vector<Node *> value;	//a list of node pointers, accessed according to attribute


public:
	Node();
	Node(int feature, bool classifier);
	Node* goToNode(int index);	//go to the node pointer at index
	void createExtension(int valueReference, bool classifier);	//can use just an int to refer
	bool isClass();

};



struct DataStruct{
	int n_features;
	int n_samples;
	vector<int> v;
	vector<vector<int> >sampleF;
	vector<int> sampleC;
};




#endif //DATACLASS_H