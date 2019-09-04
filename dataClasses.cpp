#include <vector>
#include <string>
#include <iostream>
#include "dataClasses.h"

using namespace std;


Node( ){};

Node* Node::goToNextNode(string result){
	switch (result) {
		case "tall":	//code to be executed if 'result' = 'tall'
			return nextA;
		case "short":	//code to be executed if result = 'short'
			return nextB;
		default:		//if no valid result - return null
			return nullptr;
	}
}