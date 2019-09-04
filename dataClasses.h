#ifndef DATACLASS_H
#define DATACLASS_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

//Make entropy a member? Or keep separate? If data changes, entropy changes... but so does member count etc.
class Node{
private:
	string name;
	Node* nextA;
	Node* nextB

public:
	Mode();
	Node* goToNextNode(string result);

};

#endif //DATACLASS_H