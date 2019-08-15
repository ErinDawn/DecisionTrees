
#include "helperFunctions.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

string& trim(string& str)
{
	string chars = "\t\n\v\f\r ";
	str.erase(0, str.find_first_not_of(chars));
	str.erase(str.find_last_not_of(chars) + 1);
    return str;
}