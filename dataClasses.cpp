#include <vector>
#include <string>
#include <iostream>
#include "dataClasses.h"

using namespace std;


DataClass(string className){
	name = className;
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