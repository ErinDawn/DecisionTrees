//test.cpp
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include "helperFunctions.h"
#include "functions.h"
#include "dataInfo.h"

using namespace std;


class 



int main() {




    //Construct DataInfo with stats about overall data
    //Using BBall data
    
    
    /*
    * Testing for DataInfo class and member functions
    */

	//creating a DataInfo based on supplied data
	//New data info created with fields
	DataInfo dataInfo;

	//create class
	dataInfo.createClass("yes");
		//expected
		//actual


    dataInfo.createClass("yes");
    cout << "2 yes classes added successfully" << endl;
	

	//add member to class

	//get memberCount for class

	//create feature

	//add member to feature

	//get memberCount for feature
   DataInfo dataInfo;
    
    //Add class member - show that multiple members of one class can be created
    dataInfo.createClass("yes");
    dataInfo.createClass("yes");

    //Show multiple classes can be added
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");

    //Show existing classes can be accessed using their getters and setters


    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    cout << "6 short classes added successfully" << endl;
    dataInfo.createFeature("height", "tall");
    dataInfo.createFeature("height", "tall");
    dataInfo.createFeature("height", "tall");
    dataInfo.createFeature("height", "tall");
    cout << "4 tall classes added successfully" << endl;
    dataInfo.createFeature("dexterity", "good");
    dataInfo.createFeature("dexterity", "good");
    dataInfo.createFeature("dexterity", "good");
    dataInfo.createFeature("dexterity", "good");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");;

    string classname1, classname2, featureName1, featureName2;
    int c1 = 0, c2 = 0, f1 = 0, f2 = 0, entropy = 0;
    classname1 = dataInfo.getClassNameAtIndex(0);
    c1 = dataInfo.getClassCountAtIndex(0);
    classname2 = dataInfo.getClassNameAtIndex(1);
    c2 = dataInfo.getClassCountAtIndex(1);

    cout << "The final set counts are:" << endl;
    cout << classname1 << " has a total count of: " << c1 << endl;
    cout << classname2 << " has a total count of " << c2 << endl;
    cout << "Total sample size is: " << c1 + c2 << endl;


    cout << "4 good and 6 bad features addedd successfully" << endl;

    float result = dataInfo.entropyOfSet();
    cout << "Entropy of set is: " << result << " ::: expected = 0.722" << endl;



};