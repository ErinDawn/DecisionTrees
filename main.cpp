#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include "buildTree.h"
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"

using namespace std;

int runTree(vector<int> singleItem, Node* tree, ReferenceTable table){
    Node* current;
    current = tree;
    bool isClass = current->getClassifier();
    int feature = current->getFeature();
        int nextIndex = singleItem[feature];
    int result;

    if (current == nullptr){
        cout << "Empty tree" << endl;
        return -999;
    }
    if (isClass){
        //if node is a class, return the class
        cout << "Class found, returning "<< feature << endl;
        cout << "Class found, returning "<< table.classList[feature] << " " << feature << endl;
        return feature;
    } else {
        cout << "Assessing feature: " << feature;
        cout << " " << table.featureNames[feature] << " " << endl;
        // if (feature == 0){ cout << " height " << endl;}
        // if (feature == 1){ cout << " dexterity " << endl;}
        // if (feature == 2){ cout << " fitness " << endl;}
        //if the node isn't a class, and isn't null, assess the feature.
        current = current->ptrList[nextIndex];
        cout << "calling runTree on next pointer" << endl;
        result = runTree(singleItem, current, table);
        return result;
    }
};

//refactor for use with a reference list - to make data agnostic
void printTree(Node* tree, string branch, int level, ReferenceTable table){
    //branch should start empty
    Node* current;
    current = tree;
    bool isClass = current->getClassifier();
    int feature = current->getFeature();
    if (!isClass){
        cout << "level " << level << " feature " << feature;
        cout << " " << table.featureNames[feature] << " " << endl;
        // if (feature == 0){ cout << " height" << endl;}  //Refactor using a reference table
        // if (feature == 1){ cout << " dexterity" << endl;}
        // if (feature == 2){ cout << " fitness" << endl;}
        branch = branch + "--------";
        level++;
        for (int i = 0; i < 5; i++){
            //if nextPtr is not null
            Node* next = tree->ptrList[i];
            if (next != nullptr){
                cout << branch << " option " << i << " ";
                printTree(next, branch, level, table);
            }
        }
    }
    
    if (isClass){
        cout << "level " << level << " class " << feature;
        cout << " " << table.classList[feature] << " " << endl;
        // if (feature == 0){ cout << " not professional" << endl;}
        // if (feature == 1){ cout << " professional" << endl;}
    }
};


ReferenceTable translator(){
    ReferenceTable table;
    table.verboseList.empty();
    table.classList.empty();
    table.featureNames.empty();
    string delim = ",";
    //get input from user
    string input = "";
    int n_features;
    int n_options;
    int n_classes;
    float minVal, maxVal;
    int buckets;
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
    cout << n_features << " number of features" << endl;
    table.n_features = n_features;
    cout << "*********************************************************" << endl;
    cout << "Next, consider the features in the order they will are listed in the data file." << endl;
    cout << "*********************************************************" << endl;
    for (int i = 0; i < n_features; i++){
        table.strings.clear();
        n_options = 0;
        cout << "**********" << endl;
        cout << "What is the name of data feature " << i << "? (case sensitive)" << endl;
        getline(cin, input);
        table.featureNames.push_back(input);
        //add 'input' to the vector featureName list

        ////////////////////////CREATE RANGE OPTION IN REFERENCETABLE ///////////////////

        cout << "Is this data feature a numerical range? Enter y or n" << endl;
        getline(cin, input);
        if (input == "y"){
            cout << "What is the minimum value for this feature in the dataset?";
            cout << "Enter in decimal format - i.e. 1.0" << endl;
            getline(cin, input);
            stringstream numberStream(input);
            if(numberStream >> minVal){
                break;
            }

            cout << "What is the maximum value for this feature in the dataset?";
            cout << "Enter in decimal format - i.e. 1.0" << endl;
            getline(cin, input);
            numberStream << input;
            if(numberStream >> maxVal){
                break;
            }            

            cout << "How many buckets should this feature be separated into?" << endl;
            getline(cin, input);
            numberStream << input;
            if(numberStream >> buckets){
                break;
            }

        }

        /////////////////////////////////////////String version///////////////
        while (true){
            cout << "**********" << endl;
            cout << "How many possible feature values exist for " << input << "?" << endl;
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
                cout << "What is possible feature value " << j << "?" << endl;
                getline(cin, input);
                table.strings.push_back(input);
                break;
            }
        
        //currently acceptable only with strings
        }/////////////////////////////////////////////////////////////////////
        table.verboseList.push_back(table.strings);
        table.strings.clear();
    }

    while (true){
        cout << "***************************************************" << endl;
        cout << "How many possible classes does the dataset contain?" << endl;
        getline(cin, input);
        
        stringstream numberStream(input);
        if(numberStream >> n_classes){
            break;
        }
        cout << "Invalid number. Please try again." << endl;  
    }
    for (int j = 0; j < n_classes; j++){
            while (true){   
                cout << "**********" << endl;
                cout << "What is possible class name " << j << "?" << endl;
                getline(cin, input);
                table.classList.push_back(input);
                break;
            }
    }
    while (true){
        cout << "*************************************************" << endl;
        cout << "How many data samples are in the dataset?" << endl;
        getline(cin, input);
        
        stringstream numberStream(input);
        if(numberStream >> n_classes){
            table.n_samples = n_classes;
            break;
        }
        cout << "Invalid number. Please try again." << endl;  
    }
    return table;
};

void translate(ReferenceTable table, string fileName){
    ifstream in(fileName);
    ofstream out;
    out.open("newdata.txt");
    string inString;
    int optionIndex;
    int count = 0;
    int index = 0;
    while (getline(in, inString)){
        int length = inString.length();
        size_t pos = 0;
        string token;
        int featureNumber = 0;
        while ((pos = inString.find(",")) != string::npos) {    //take each feature value from the string
            token = inString.substr(0, pos);
            trim(token);
            //find what index this corresponds to in table[featureNumber]
            optionIndex = table.isFeatureOption(token, featureNumber);
            //write the index to file
            out << optionIndex << ", ";

            inString.erase(0, pos + 1);
            featureNumber++;
        }
        //*************************FIX THIS PLEASE
        
        trim(inString); //last item in the string will be the class
        optionIndex = table.isClass(inString, featureNumber);
        out << optionIndex << endl;
        index++;
    }
    out.close();
};



int main() {

ReferenceTable newTable;
newTable = translator();
newTable.printTable();
translate(newTable, "example.txt");


DataStruct newData;
int n_features = newTable.n_features;
int n_samples = 10;
newData = openFromFile("newdata.txt", n_features, n_samples);
newData.expandedList.clear();
newData.remaining_features = n_features;    //n_features will have to be added in
cout << "************************************************" << endl;

//pass inData into buildTree function

Node* rootNode;
rootNode = new Node();
buildTree(rootNode, newData);
cout << "************************************************" << endl;

Node* tree;
tree = rootNode;

//Use tree to classify a new data item
//i.e. an expected 0 value
cout << "creating test vector" << endl;
vector<int> dataItem(2, 0);
dataItem.push_back(2);
int temp1, temp2, temp3;

cout << "Test vector set to 0, 0, 2" << endl;
temp1 = dataItem[0];
temp2 = dataItem[1];
temp3 =  dataItem[0];
cout << temp1 << ", " << temp2 << ", " << temp3 << endl;
cout << "Expected class = 0 - Not professional" << endl;

int finalClass;
cout << "************************************************" << endl;
cout << "Running tree" << endl;\
finalClass = runTree(dataItem, tree, newTable);
cout  << "Class returned = " << finalClass << endl;


//i.e. an expected 1 value
cout << "Test vector set to 1, 0, 2" << endl;
dataItem[0] = 1;
dataItem[1] = 1;
dataItem[2] = 2;

temp1 = dataItem[0];
temp2 = dataItem[1];
temp3 =  dataItem[2];
cout << temp1 << ", " << temp2 << ", " << temp3 << endl;
cout << "Expected class = 1 - Professional" << endl;

cout << "************************************************" << endl;
cout << "Running tree" << endl;
finalClass = runTree(dataItem, tree, newTable);
cout  << "Class returned = " << finalClass << endl;
cout << "************************************************" << endl;


printTree(tree, "", 1, newTable);
newTable.printTable();


return 0;
}

