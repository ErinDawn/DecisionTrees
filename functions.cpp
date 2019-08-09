//Entropy - how much disorder in information a certain set contains.
// Entropy = sum of p of i log2 (p of i)

//Information Gain - How much information a particular bit of data gives us

#include <iostream>
#include <cmath>
#include <string>
#include "helperFunctions.h"

using namespace std;



/*
* Function to split incoming data into its features and classes
* TODO: use dataFeature and dataClass classes to sep. the data
* Create vector of features and vector of classes   
* If feature exists in vector:
*        Look at feature option
*        If option exists
*            Add to option count and continue
*        Else
*            Add option and make option count = 1
*    Else add feature, add feature option and make option count = 1
* If class exists in vector:
*        Add to class count and continue
*    Else
*        Create class and make class count = 1
*/
//Will my data have headers? If so, process may change slightly, current data samples indicate no
//Alternately, can I have these entered by the user?
int countColumns(string line, string delim){
    int length = line.length();
    int features = 0;

    size_t pos = 0;
    string token;
    while ((pos = line.find(delim)) != string::npos) {
        token = line.substr(0, pos);
        trim(token);
        cout << token << endl;
        line.erase(0, pos + delim.length());
        features++;
    }
    trim(line);
    cout << line << endl << endl;

    return features;

}


/*
* Function to build tree based on Info Gain
*/

