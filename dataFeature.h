#ifndef DATAFEATURE_H
#define DATAFEATURE_H

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

//Make entropy a member? Or keep separate? If data changes, entropy changes... but so does member count etc.
class FeatureOption{
private:
	string name;
	int memberCount;

public:
	FeatureOption(string optionName);
	string getName();
	int getMemberCount();
}


class DataFeature{
private:
	string name;
	//vector of feature 'options'?

public:
	DataFeature(string featureName);
	string getName();
	void addOption();
};





#endif //DATAFEATURE_H