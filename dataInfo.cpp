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

void FeatureOption::addClassRelationship(string className){
	//check associatedClass to see if class exists
	int length = associatedClass.size();
	int tempLength = 0;
	int i = 0;
	string temp;
	bool exists = false;
	if (length > 0){
		for (i = 0; i < length; i++){
			temp = associatedClass[i].getName();
			if (temp == className){
				exists = true;
				break;
			}
		}
	}
	if (exists) {
		associatedClass[i].addMember();
		tempLength = associatedClass[i].getMembers();
	} else{
		DataClass newClass(className);
		tempLength = newClass.getMembers();
		associatedClass.push_back(newClass);
	}
}
/***************************************************************
******Should this be by name instead? Potential refactor********
***************************************************************/
int FeatureOption::getAssociatedClassCountAtIndex(int index){
	int result = associatedClass[index].getMembers();
	return result;
}

string FeatureOption::getAssociatedClassNameAtIndex(int index){
	string className = associatedClass[index].getName();
	return className;
}

/////////////////End feature option prototypes/////////////


///////////////////////////////////////////////////////////
////////////DataFeature function prototypes////////////////
DataFeature::DataFeature(string featureName, string featureOption){
	name = featureName;
	addOption(featureOption);
}

string DataFeature::getName(){
	return name;
}

int DataFeature::getMembers(){
	int length = optionList.size();
	return length;
}

void DataFeature::addOption(string featureOption){
	//Does featureOption exist?
	string temp;
	int length, i;
	bool exists = false;
	length = optionList.size();
	for (i = 0; i > length; i++){
		temp = optionList[i].getName();
		if (featureOption == temp){
			exists = true;
			break;
		}
	}
	if (exists){	//add one to that count
		optionList[i].addMember();
	} else{
		//create new option
		FeatureOption newOption(featureOption);
		optionList.push_back(newOption);
		length = optionList.size();
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

int DataFeature::getOptionCountAtIndex(int index){
	int temp;
	temp = optionList[index].getMemberCount();
	return temp;
}

float DataFeature::entropyOfSet(int totalSamples){
	int length = optionList.size();
	int memberCount = 0;
	float result = 0.0;
	float piVal = 0.0;
	float entropyVal = 0.0;


	for (int i = 0; i < length; i++){
		memberCount = optionList[i].getMemberCount();
		piVal = pi(memberCount, totalSamples);
		entropyVal = calcEntropy(piVal);
		result = result + entropyVal;
	}

	return result;
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
	int tempLength = 0;
	int i = 0;
	string temp;
	bool exists = false;
	if (length > 0){
		for (i = 0; i < length; i++){
			temp = classList[i].getName();
			if (temp == className){
				exists = true;
				break;
			}
		}
	}
	if (exists) {
		classList[i].addMember();
		tempLength = classList[i].getMembers();
	} else{
		DataClass newClass(className);
		tempLength = newClass.getMembers();
		classList.push_back(newClass);
	}
	
}

/****************************
******TODO*******************
*****************************/
void DataInfo::createFeature(string featureName, string featureOption){	//create a new data feature
	//Check featureList to see if feature exists
	int fIndex = isFeatureMember(featureName);
	if (fIndex >= 0){
		int oIndex;
		oIndex = featureList[fIndex].isOptionMember(featureOption);
		if (oIndex >= 0){
			//option exists
			featureList[fIndex].addOption(featureOption);	//auto adds member if option 
			//featureList[fIndex].optionList[oIndex].addMember();
		} else {

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

int DataInfo::getSampleCount(){	//adds all members up to give total sample size, incl. all classes
	int sampleCount = 0;
	int length = 0;
	int temp;
	length = getNumOfClasses();
	for (int i =0; i < length; i++){
		temp = getClassCountAtIndex(i);
		sampleCount = sampleCount + temp;
	}
	return sampleCount;
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

//get number of options
int DataInfo::getFeatureOptionCountAtIndex(int index){
	int temp;
	temp = featureList[index].getMembers();
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
	string temp;
	for (int i = 0; i < length; i++){
		temp = featureList[i].getName();
		if (temp == featureName){
			return i;
		}
	}
	cout << "Feature " << featureName << " not found" << endl;
	return -1;
}

float DataInfo::totalEntropy(){
	int setSize;
	float result = 0.0;
	float piVal = 0.0;
	float entropyVal = 0.0;

	setSize = getSampleCount();
	int length = getNumOfClasses();
	int memberCount;

	for (int i = 0; i < length; i++){
		memberCount = classList[i].getMembers();
		piVal = pi(memberCount, setSize);
		entropyVal = calcEntropy(piVal);
		result = result + entropyVal;
	}

	return result;
}

float DataInfo::getEntropyOfFeatureAtIndex(int index){
	//**********TODO - Correct - need a class count for each FeatureOption
	//
	int temp;
	int i;
	int optionListLength = featureList[index].optionList.size();
	int associatedClassListLength;
	int j = 0;
	//Iterate through the option list - 
	//get all associated class counts
	//include each pi-entropy in overall sum
	for (i = 0; i < optionListLength; i++ ){
		int associatedClassListLength = featureList[index].optionList[i].associatedClass.size();
		for( j = 0; j < associatedClassListLength; j++){
			temp = featureList[index].optionList[i].getAssociatedClassCountAtIndex(j);
		}
	}
	


	float result;
	int totalSample = getSampleCount();
	result = featureList[index].entropyOfSet(totalSample);
	return result;
}

///////////////////End DataInfo prototypes//////////////////