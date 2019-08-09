#ifndef DATACLASS_H
#define DATACLASS_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

//Make entropy a member? Or keep separate? If data changes, entropy changes... but so does member count etc.
class DataClass{
private:
	string name;
	int members;

public:
	DataClass(string className);
	string getName();
	int getMembers();
	void addMember();
	float getEntropy();
};

#endif //DATACLASS_H