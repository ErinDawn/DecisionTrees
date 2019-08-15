#include "dataInfo.h"
#include "helperFunctions.h"
#include "functions.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////
///////////////////FeatureOption Prototypes/////////////////
FeatureOption::FeatureOption(string optionName){

	name = trim(optionName);
	memberCount = 1;
} 

string FeatureOption::getName(){
	return name;
}

int FeatureOption::getMemberCount(){
	return memberCount;
}

void FeatureOption::addMember(){
	memberCount++;
}

/////////////////End feature option prototypes/////////////


///////////////////////////////////////////////////////////
////////////DataFeature function prototypes////////////////
DataFeature::DataFeature(string featureName, string featureOption){
	addOption(featureOption);
}

string DataFeature::getName(){
	return name;
}

void DataFeature::addOption(string featureOption){
	cout << "Add option function entered (dataFeature)" << endl;
	//Does featureOption exist?
	string temp;
	int length, i;
	bool exists = false;
	length = optionList.size();
	cout << "Length of option list is: " << length << endl;
	for (i = 0; i > length; i++){
		cout << "FOR loop entered" << endl;
		temp = optionList[i].getName();
		cout << "feature option name is: " << temp << endl;
		if (featureOption == temp){
			exists = true;
			cout << temp << " exists already" << endl;
			break;
		}
	}
	if (exists){	//add one to that count
		optionList[i].addMember();
		cout << featureOption << " count increased" << endl;
	} else{
		//create new option
		FeatureOption newOption(featureOption);
		//newOption.addMember();
		optionList.push_back(newOption);
		cout << "new " << featureOption << " option added" << endl;
		length = optionList.size();
		cout << "Length of option list is: " << length << endl;
	}
}

int DataFeature::isOptionMember(string optionName){
	int length = optionList.size();
	for (int i; i < length; i++){
		string temp = optionList[i].getName();
		if (temp == optionName){
			return i;
		}
	}
	return -1;
}

/////////////////End DataFeature prototypes////////////////



//////////////////////////////////////////////////////////
//////////////DataClass function prototypes///////////////
DataClass::DataClass(string className){
	name = trim(className);
	members = 1;
};

string DataClass::getName(){
	return name;
}

int DataClass::getMembers(){
	return members;
}

void DataClass::addMember(){
	members++;
}

////////End DataClass prototypes//////////////////////////


/////////////////////////////////////////////////////////
/////////////////DataInfo function prototypes////////////
DataInfo::DataInfo(){	//Constructor
}

void DataInfo::createClass(string className){	//Create a new data class
	//check classList to see if class exists
	int length = classList.size();
	cout << "Current number of classes is: " << length << endl;
	int tempLength = 0;	//*********************DEBUGGING******************
	int i = 0;
	string temp;
	bool exists = false;
	if (length > 0){
		for (i = 0; i < length; i++){
			temp = classList[i].getName();
			if (temp == className){
				exists = true;
				cout << className << " already exists" << endl;
			}
		}
	}
	if (exists) {
		cout << "Adding 1 to " << className << " count" << endl;
		classList[i].addMember();
				tempLength = classList[i].getMembers();
		cout << "New " << className << " count is: " <<  tempLength << endl;
	} else{
		cout << className << " does not yet exist... Creating class now" << endl;
		DataClass newClass(className);
		tempLength = newClass.getMembers();
		cout << "The number of members in the new class should = 1... actual members = " << tempLength << endl;
		classList.push_back(newClass);
	}
	
}

void DataInfo::createFeature(string featureName, string featureOption){	//create a new data feature
	//Check featureList to see if feature exists
	int fIndex = isFeatureMember(featureName);
	if (fIndex >= 0){
		int oIndex;
		oIndex = featureList[fIndex].isOptionMember(featureOption);
		if (oIndex >= 0){
			//option exists
			featureList[fIndex].addOption(featureOption);
			//featureList[fIndex].optionList[oIndex].addMember();
		}

	} else {
		DataFeature newFeature(featureName, featureOption);
		featureList.push_back(newFeature);
	}
	
}

int DataInfo::getNumOfFeatures(){	// return the number of data features
	return featureList.size();
}

int DataInfo::getNumOfClasses(){	//return he number of data classes
	return classList.size();
}

string DataInfo::getClassNameAtIndex(int index){
	string temp;
	temp = classList[index].getName();
		return temp;
}

int DataInfo::getClassCountAtIndex(int index){
	int result = classList[index].getMembers();
	return result;
}

string DataInfo::getFeatureNameAtIndex(int index){
	string temp;
	temp = featureList[index].getName();
		return temp;
}


bool DataInfo::isClassMember(string className){
	int length = classList.size();
	for (int i; i < length; i++){
		string temp = classList[i].getName();
		if (temp == className){
			return true;
		}
	}
	return false;
}

int DataInfo::isFeatureMember(string featureName){
	int length = featureList.size();
	for (int i; i < length; i++){
		string temp = featureList[i].getName();
		if (temp == featureName){
			return i;
		}
	}
	return -1;
}

float DataInfo::entropyOfSet(){
	int class1 = 0, class2 = 0, setSize = 0;
	float val1 = 0.0, val2 = 0.0, val3 = 0.0;
	setSize = classList.size();
	if (setSize == 2){
		class1 = classList[0].getMembers();
		class2 = classList[1].getMembers();

		val1 = pi(class1, setSize);
		val2 = pi(class2, setSize);
		val3 = entropy(val1) + entropy(val2);

	} else {
		cout << "entropyOfSet function error" << endl;
		return -999;
	}
	return val3;
	//sum of entropy for each class - i.e.
	// entropy(0.2) + entropy(0.8)
}

///////////////////End DataInfo prototypes//////////////////