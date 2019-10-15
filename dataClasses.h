#ifndef DATACLASS_H
#define DATACLASS_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;


struct DataStruct{
	int n_features;
	int remaining_features;
	int n_samples;
	int n_classes;
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
	vector<vector<float> > rangeList;
	vector<float> rangeItem;

	int n_features;
	int n_classes;
	int n_samples;
	vector<string> classList;
	vector<string> featureNames;
	vector<bool> numericalRange;

	/*
	* Checks the verboseList at a p[articular feature index
	* compares the given string to see which value it matches 
	* returns the index of the matching feature value
	*/
	int isFeatureOption(int index, string checkString){
		int length = verboseList[index].size();
		for (int i = 0; i < length; i++){
			if (checkString == verboseList[index][i]){
				return i;
			}
		}
		cout << "Err - feature option not found" << endl;
		return -999;
	}

	/*
	* Checks the range table to see which 'bucket'
	* a value belongs to. Returns the index of that bucket
	*/
	int isRangeOption(int featureNumber, string checkString){
		//convert checkstring to float value
		float value;
		float range;
		int temp;
		float checkMe;

		stringstream numberStream(checkString);
		numberStream >> value;
		int length = rangeItem.size();
		int lastI = length -1;
		int buckets = rangeList[featureNumber].size();	/////////////////////////////////////////////////////
		cout << "There are " << buckets << " buckets for this vector." << endl;	///////////////////////////////
		cout << "Considering value " << value << endl;
		for (int i = 0; i < length; i++){
			cout << "Looking in index " << i << endl;
			checkMe = rangeList[featureNumber][i];
			cout << "Current range is < " << checkMe << endl;
		//if it's less than current range return, otherwise, look at next i, which is bigger
			if (value < rangeList[featureNumber][i]){	//if less than this, belongs in the bucket
				//bucket number is i
				range = rangeList[featureNumber][i];
				range = (range*100);
    			temp = range;
    			range = temp * 1.0;
    			range = range / 100;
				cout << "Belongs in range < " << range << endl;
				cout << "Bucket " << i << endl;
				return i;
			}
			if (buckets == 1){
				cout << "Bucket count registered" << endl;
				//bucket number is i
				range = rangeList[featureNumber][i];
				range = (range*100);
    			temp = range;
    			range = temp * 1.0;
    			range = range / 100;
				cout << "Belongs in range > " << range << endl;
				cout << "Bucket " << i << endl;
				return i;
			}
			if (i == lastI){	//if the last bucket, value must fall into this one
				//bucket number is i
				range = rangeList[featureNumber][i];
				range = (range*100);
    			temp = range;
    			range = temp * 1.0;
    			range = range / 100;
				cout << "Belongs in range > " << range << endl;
				cout << "Bucket " << i << endl;
				return i;
			}
			buckets--;
		}
		cout << "Error. No corresponding bucket found." << endl;
		return -999;
	}

	/*
	* Checks through the reference table for
	* class, as a string, returns the index of
	* that class in the reference table
	*/
	int isClass(string checkString, int index){
		int length = classList.size();
		for (int i = 0; i < length; i++){
			if (checkString == classList[i]){
				return i;
			}
		}
		return -999;
	}

	/*
	* Prints the reference table, so user can quickly see
	* data points and corresponding plain English values
	*/
	void printTable(){
		cout << endl << "***********PRINTING REFERENCE TABLE***********" << endl;
		int rangeIndex = 0;
		for (int i = 0; i < n_features; i++){
			int length = verboseList[i].size();
			for (int j = 0; j < length; j++){
				cout << "Item[" << i << "][" << j << "] = " << verboseList[i][j] << endl;
			}
			if (numericalRange[i]){	//print the range buckets
				float min, max;
				int inLength;
				inLength = rangeList[rangeIndex].size();
				cout << "Total number of buckets = " << inLength << endl;
				for (int k = 0; k < inLength; k++){
					max = rangeList[rangeIndex][k];
					cout << "max = " << max << endl;
					if (k == 0){
						cout << "---------- Less than " << max << endl;
					} else if (k == inLength-1){
						cout << "---------- Equal or greater than " << max << endl;
					} else {
						cout << "---------- Equal or greater than " << min;
						cout << " and less than " << max << endl;
					}
					min = max;
				}
				rangeIndex++;
			}	
		}
		int length = classList.size();
		cout << "With classes: ";
		for (int i = 0; i < length; i++){
			cout << classList[i] << " ";
		}
		cout << endl << "**************END REF TABLE**************" <<endl << endl;	
	}
};

#endif //DATACLASS_H