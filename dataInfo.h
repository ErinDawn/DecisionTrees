#ifndef DATAFEATURE_H
#define DATAFEATURE_H

#include "helperFunctions.h"
#include "functions.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;


class FeatureOption{
private:
	string name;
	int memberCount;

public:
	FeatureOption(string optionName);
	string getName();
	int getMemberCount();
	void addMember();	//
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
};



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
	float entropyOfSet();	//Sum of entropy of all classes
	string getClassNameAtIndex(int index);
	int getClassCountAtIndex(int index);
	string getFeatureNameAtIndex(int index);
};

#endif //DATAFEATURE_H