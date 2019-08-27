#ifndef DATAFEATURE_H
#define DATAFEATURE_H

#include "helperFunctions.h"
#include "functions.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

class DataClass{
private:
	string name;
	int members;

public:
	DataClass(string className);
	string getName();
	int getMembers();
	void addMember();
};

class FeatureOption{
private:
	string name;
	int memberCount;
	vector<DataClass> associatedClass;

public:
	FeatureOption(string optionName);
	string getName();
	int getMemberCount();
	void addMember();	//
	void addClassRelationship(string className);
	int getAssociatedClassCountAtIndex(int index);
	string getAssociatedClassNameAtIndex(int index);
};


class DataFeature{
private:
	string name;
	vector<FeatureOption> optionList;

public:	
	DataFeature(string featureName, string featureOption);
	string getName();
	void addOption(string featureOption);
	int isOptionMember(string optionName);
	int getOptionCountAtIndex(int index);
	float entropyOfSet(int totalSamples);
	int getMembers();
};






class DataInfo{
private:
	vector<DataFeature> featureList;
	vector<DataClass> classList;
public:
	DataInfo();
	void createClass(string className);
	void createFeature(string featureName, string featureOption);
	int getNumOfFeatures();
	int getNumOfClasses();
	//bool isFeatureMember(string featureName);	refactored below
	int isFeatureMember(string featureName);
	bool isClassMember(string className);	//not in use
	float totalEntropy();	//Sum of entropy of all classes
	string getClassNameAtIndex(int index);
	int getClassCountAtIndex(int index);
	string getFeatureNameAtIndex(int index);
	int getFeatureOptionCountAtIndex(int index);
	int getSampleCount();
	float getEntropyOfFeatureAtIndex(int index);
};

#endif //DATAFEATURE_H