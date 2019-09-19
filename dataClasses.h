#ifndef DATACLASS_H
#define DATACLASS_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

struct DataStruct{
	int n_features;
	int remaining_features;
	int n_samples;
	vector<int> v;
	vector<vector<int> >sampleF;
	vector<int> sampleC;
	vector<int> expandedList;
	void printMatrix(){
		for (int i = 0; i < n_samples; i++){
			cout << "Sample " << i << endl;
			cout << " with features: ";
			for (int j = 0; j < n_features; j++){
				cout << sampleF[i][j] << " ";
			}
			cout << " and class: " << sampleC[i] << endl;
		}
		
	}
	bool alreadyExpanded(int feat){
		bool result;
		result = find(v.begin(), v.end(), feat) != v.end();
		return result;
	}
};


//Make entropy a member? Or keep separate? If data changes, entropy changes... but so does member count etc.
class Node{
private:
	int feature;
	bool classifier;	//if classifier is true, resulting class node
	
public:
	Node();
	Node(int value, bool isClass);
	Node* goToNode(int index);	//go to the node pointer at index
	bool isClass();
	void setFeature(int feat);
	int getFeature();
	void setClassifier(bool classifier);
	bool getClassifier();
	vector<Node *> nextPtr;	//a list of node pointers, accessed according to attribute
	Node* getNextNode(int next);
	void testNode();
};








#endif //DATACLASS_H