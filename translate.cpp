#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"
#include "translate.h"

using namespace std;

float roundAlt(float var) 
{
    var = (var*100);
    int temp = var;
    var = temp * 1.0;
    var = var / 100;
    return var; 
}



ReferenceTable translator(){
    ReferenceTable table;
    table.verboseList.clear();
    table.classList.clear();
    table.featureNames.clear();
    table.numericalRange.clear();
    string delim = ",";
    //get input from user
    string input = "";
    int n_features;
    int n_options;
    int n_classes;
    int n_samples;
    float minVal, maxVal, buckets, temp;
    cout << "Some information is required about the data set" << endl;
    while (true){
        cout << "*************************************************" << endl;
        cout << "How many data features considered by the dataset?" << endl;
        getline(cin, input);
        
        stringstream numberStream(input);
        if(numberStream >> n_features){
            break;
        }
        cout << "Invalid number. Please try again." << endl;  
    }
    table.n_features = n_features;
    cout << "*********************************************************" << endl;
    cout << "Next, consider the features in the order they will are listed in the data file." << endl;
    cout << "Note - all values are case sensitive." << endl;
    cout << "*********************************************************" << endl << endl;
    
    for (int i = 0; i < n_features; i++){
        table.strings.clear();
        n_options = 0;
        cout << "What is the name of data feature " << i << "?" << endl;
        getline(cin, input);
        table.featureNames.push_back(input);
        //add 'input' to the vector featureName list
        cout << endl << endl;
        cout << "Is this data feature a numerical range? Enter y or n" << endl;
        getline(cin, input);
        if (input == "y"){
            table.numericalRange.push_back(true);;
            cout << endl << endl;
            cout << "What is this features minimum value?";
            
            while(true){
                getline(cin, input);
                stringstream numberStream(input);
                if(numberStream >> temp){
                    minVal = (temp* 1.0);   //make sure temp is as float
                    break;
                }
            }
            cout << endl << endl;
            cout << "What is this feature's maximum value?" << endl;
            while(true){
                getline(cin, input);
                stringstream numberStream(input);

                if(numberStream >> temp){
                    maxVal = (temp * 1.0);
                    break;
                }
            }
            cout << endl << endl;
            cout << "How many buckets should this feature be separated into?" << endl;
            while(true){
                getline(cin, input);
                stringstream numberStream(input);
                if(numberStream >> buckets){
                    break;
                }
            }
            float result = (maxVal - minVal) / (buckets);
            result = roundAlt(result);
            float tempMin = 0.0;
            float tempMax = minVal + result;
            float j = 0.0;
            string rangeAsString;
            table.rangeItem.clear();
            int buK = 0;

            for (int k = 0; k < buckets; k++){
                //first bucket = minval + result
                tempMax = roundAlt(tempMax);    //rounded
                //push value to vector
                rangeAsString = "< " + to_string(tempMax);
                table.rangeItem.push_back(tempMax);;
                //increment tempMax;
                tempMax = tempMax + result;

            }

            //for each of these - create a new entry into
            table.strings.push_back("RANGE");
            table.rangeList.push_back(table.rangeItem);
            table.verboseList.push_back(table.strings);
            table.strings.clear();
        } else {
            table.numericalRange.push_back(false);

            /////////////////////////////////////////String version///////////////
            while (true){
                cout << "**********" << endl;
                cout << endl << endl;
                cout << "How many possible feature values exist for this feature?" << endl;
                getline(cin, input);
                stringstream numberStream(input);
                if(numberStream >> n_options){
                    break;
                }
                cout << "Invalid number. Please try again." << endl;  
            }

            for (int j = 0; j < n_options; j++){
                while (true){   //currently acceptable only with strings
                    cout << "**********" << endl;
                    cout << endl << endl;
                    cout << "What is possible feature value " << j << "?" << endl;
                    getline(cin, input);
                    table.strings.push_back(input);
                    break;
                }
            }
            table.verboseList.push_back(table.strings);
            table.strings.clear();
        }
    }

    while (true){
        cout << "***************************************************" << endl;
        cout << endl << endl;
        cout << "How many possible classes does the dataset contain?" << endl;
        getline(cin, input);
        
        stringstream numberStream(input);
        if(numberStream >> n_classes){
            break;
        }
        cout << "Invalid number. Please try again." << endl;  
    }
    table.n_classes = n_classes;
    for (int j = 0; j < n_classes; j++){
            while (true){   
                cout << "**********" << endl;
                cout << endl << endl;
                cout << "What is possible class name " << j << "?" << endl;
                getline(cin, input);
                table.classList.push_back(input);
                break;
            }
    }
    while (true){
        cout << "*************************************************" << endl;
        cout << endl << endl;

        cout << "How many data samples are in the dataset?" << endl;
        getline(cin, input);
        
        stringstream numberStream(input);
        if(numberStream >> n_samples){
            table.n_samples = n_samples;
            break;
        }
        cout << "Invalid number. Please try again." << endl;  
    }
    return table;
};

void translate(ReferenceTable table, string fileName){
    cout << "Translating file using table..." << endl;
    ifstream in(fileName);
    ofstream out;
    out.open("newdata.txt");
    string inString;
    int optionIndex;
    int count = 0;  //to iterate through the rangeVector
    // int index = 0;
    bool check;
    while (getline(in, inString)){
        int length = inString.length();
        size_t pos = 0;
        string token;
        int featureNumber = 0;
        count = 0;
        //count starting at zero for each sample
        //
        //string table count starting at zero
        //go through the verbose list - if "RANGE" refer to the range table
        //once range table refered to rangeTableCount++

        while ((pos = inString.find(",")) != string::npos) {    //take each feature value from the string
            check = table.numericalRange[featureNumber];    //check if feature should be a range
            if (check){// range option
                //cout << "Translating a range option..." << endl;
                token = inString.substr(0, pos);
                trim(token); // token is a float value

                                    //cout << "Checking range bucket for feature " << count << endl;
                //find what index this corresponds to in table[count]
                optionIndex = table.isRangeOption(count, token);
                //write the index to file
                out << optionIndex << ", ";
                inString.erase(0, pos + 1);
                featureNumber++;    //we read one from string, then increment feature count
                count++;    //we read one from range, then increment count
            } else {    //string option
                //cout << "Translating a string option..." << endl;
               token = inString.substr(0, pos);
                trim(token);
                //find what index this corresponds to in table[featureNumber]
                optionIndex = table.isFeatureOption(featureNumber, token);
                //write the index to file
                out << optionIndex << ", ";
                inString.erase(0, pos + 1);
                featureNumber++; 
            }
        }
        trim(inString); //last item in the string will be the class
        optionIndex = table.isClass(inString, featureNumber);
        out << optionIndex << endl;
        // index++;
    }
    out.close();
};