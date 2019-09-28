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


class Node{
private:
	int feature;
	bool classifier;	//if classifier is true, resulting class node
	
public:
	Node();
	Node(int value, bool isClass);
	bool isClass();
	void setFeature(int feat);
	int getFeature();
	void setClassifier(bool classifier);
	bool getClassifier();
	vector<Node *> ptrList;	//a list of node pointers, accessed according to attribute
	void testNode();
};

struct ReferenceTable{
	vector<string> strings;
	vector<vector<string> >verboseList;
	int n_features;
	int n_classes;
	int n_samples;
	vector<string> classList;
	vector<string> featureNames;
	int isFeatureOption(string checkString, int index){
		int length = verboseList[index].size();
		for (int i = 0; i < length; i++){
			if (checkString == verboseList[index][i]){
				return i;
			}
		}
		return -999;
	}
	int isClass(string checkString, int index){
		int length = classList.size();
		for (int i = 0; i < length; i++){
			if (checkString == classList[i]){
				return i;
			}
		}
		return -999;
	}
	void printTable(){
		cout << "****PRINTING REFERENCE TABLE****" << endl;
		for (int i = 0; i < n_features; i++){
			int length = verboseList[i].size();
			for (int j = 0; j < length; j++){
				cout << "Item[" << i << "][" << j << "] = " << verboseList[i][j] << endl;
			}
		}
		int length = classList.size();
		cout << "With classes: ";
		for (int i = 0; i < length; i++){
			cout << classList[i] << " ";
		}
		cout << "****END REF TABLE****" <<endl;
		
	}
};

#endif //DATACLASS_H