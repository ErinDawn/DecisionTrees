#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include "helperFunctions.h"
#include "functions.h"
#include "dataClasses.h"

using namespace std;

int main() {

    //read text in line by line, separated by a deliminator
    //Print it line by line removing white space
    //this will help to prep the data

    int featureCount = 0;
    int classOptions = 0;

    string line;
    ifstream dataFile("example.txt");
    if (dataFile.is_open()) {
        while (getline (dataFile, line)) {
            cout << line << '\n';
            //count how many items there are, assume they are separated by comma
            featureCount = countColumns(line, ",");
        }
        dataFile.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    cout << endl << featureCount << " features counted" << endl;
    cout << classOptions << " different classes counted" << endl;   //currently not handling

    //end read in



    //check entropy functions work as expected
   float value;

   int arrayX[3];
   arrayX[1] = 1;

   value = Entropy(0.2);
	cout << "Test function: " << value << endl;


	value = Entropy(0.5, 0.5);
	cout << "Test function2: " << value << " odds are completely balanced" << endl;

   value = Entropy(0.001, 0.999);
   cout << "Test function2: " << value << " odds are completely imbalanced" << endl;

}


// float Entropy(float representation){
//    return -(representation * log2(representation));
// }

// float Entropy(float rep1, float rep2){
//    return Entropy(rep1) + Entropy(rep2);
// }