#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include "helperFunctions.h"
#include "functions.h"
#include "dataInfo.h"

using namespace std;

int main() {

    int numOfFeatures = 2;
    int numOfClasses = 2;
    int membersOfTall = 4;
    int membersOfShort = 6;
    int membersofGood = 4;
    int membersOfBad = 6;
    int numOfProfessionals = 2;
    int numOfAmateurs = 8;


    float temp, value1, value2;
    float entropyValue;
    float entropyValue2;
    float entropy[2];
    float informationGain;
    entropyValue = pi(4, 10);
    entropyValue = calcEntropy(entropyValue);
    cout << "********************************" << endl;
    cout << entropyValue << endl;
    cout << "********************************" << endl;

    //entropy for short
    // temp = (1.0/6.0);
    // // cout << "The float value is: " << temp << endl;
    // value1 = entropy(temp);
    // cout << "The first entropy value is: " << value1 << endl;
    // temp = (5.0/6.0);
    // value2 = entropy(temp);
    // cout << "The second entropy value is: " << value2 << endl;
    // entropyValue = entropy(value1, value2);
    // cout << "The entropy for \"short\" is: " << entropyValue << endl;

    // temp = (1.0/6.0);
    // // cout << "The float value is: " << temp << endl;
    // entropy[0] = entropy(temp);
    // temp = (5.0/6.0);
    // entropy[1] = entropy(temp);
    // entropyValue = entropy(value1, value2);
    // cout << "The entropy for \"short\" is: " << entropyValue << endl;




    //************************************************************************
    //read text in line by line, separated by a deliminator
    //Print it line by line removing white space
    //this will help to prep the data

    // int featureCount = 0;
    // int classOptions = 0;

    // string line;
    // ifstream dataFile("example.txt");
    // if (dataFile.is_open()) {
    //     while (getline (dataFile, line)) {
    //         cout << line << '\n';
    //         //count how many items there are, assume they are separated by comma
    //         featureCount = countColumns(line, ",");
    //     }
    //     dataFile.close();
    // } else {
    //     cout << "Unable to open file" << endl;
    // }

    // cout << endl << featureCount << " features counted" << endl;
    // cout << classOptions << " different classes counted" << endl;   //currently not handling

    //end read in****************************************************************

    //Construct DataInfo with stats about overall data
    //Using BBall data

    DataInfo dataInfo;
    
    dataInfo.createClass("yes");
    dataInfo.createClass("yes");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createClass("no");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "short");
    dataInfo.createFeature("height", "tall");
    dataInfo.createFeature("height", "tall");
    dataInfo.createFeature("height", "tall");
    dataInfo.createFeature("height", "tall");
    dataInfo.createFeature("dexterity", "good");
    dataInfo.createFeature("dexterity", "good");
    dataInfo.createFeature("dexterity", "good");
    dataInfo.createFeature("dexterity", "good");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");
    dataInfo.createFeature("dexterity", "bad");
    cout << endl << endl;

    float result = dataInfo.totalEntropy();
    cout << "Entropy of set is: " << result << " ::: expected = 0.722" << endl;

    cout << "We added some stuff" << endl;
    cout << endl;
    string classname1, classname2, featureName1, featureName2;
    int c1 = 0, c2 = 0;
    float f1 = 0.0, f2 = 0.0;
    classname1 = dataInfo.getClassNameAtIndex(0);
    c1 = dataInfo.getClassCountAtIndex(0);
    classname2 = dataInfo.getClassNameAtIndex(1);
    c2 = dataInfo.getClassCountAtIndex(1);

    cout << "The final set counts are:" << endl;
    cout << classname1 << " has a total count of: " << c1 << endl;
    cout << classname2 << " has a total count of " << c2 << endl;
    cout << "Total sample size is: " << c1 + c2 << endl;

    f1 = dataInfo.getEntropyOfFeatureAtIndex(0);
    f2 = dataInfo.getEntropyOfFeatureAtIndex(1);
    cout << "The entropy for height is: " << f1 << endl;
    cout << "The entropy for dexterity is: " << f2 << endl;

    return 0;

}

