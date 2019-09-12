#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "buildTree.h"
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"

using namespace std;


int main() {

     DataStruct newData;
     newData = openFromFile("test.txt", 2, 10);


// //pass inData into buildTree function

//Node rootNode = buildTree(newData);
 buildTree(newData);


// ////////////////////////////////////////////////////////////////////////////////////
//     //create root node for tree
//     //if all examples are positive 
//         //return a leaf with label +
//     //if all examples are negative
//         //return a leaf with label -
//     //if no more features remain
//         //return a single node with a label = most common value for this branch


    

//     //for each in a given array,
//     //check if it should be part of the subarray (if it has feature value of type X).
//     //if yes, add to subArray, increment
//     //if not increment

//     for (int i = 0; i < n_samples; i++){

//     }




// /**********************************************************
//     int featureSet[n_features][5];     //set an array with feature row, value column
//     //set all values at -1 to begin - this denotes no feature value
//     for (int i = 0; i < n_features; i++){
//         for (int j = 0; j < 5; j++){
//             featureSet[i][j] = -1;
//         }
//     }

//     featureSet[0][0] = 0;  //height, tall
//     featureSet[0][1] = 1;  //height, short
//     featureSet[1][0] = 0;  //dexterity, good
//     featureSet[1][1] = 1;  //dexterity, bad

//     string classList[n_classes];
//     classList[0] = "yes";
//     // classList[1] = "no";
// *******************************************************************************/



//     //calc the entropy of set.
//     int positiveCount = 0;
//     int negativeCount = 0;
//     int subSet = n_samples;
//     int temp;
//     int featureCount[n_features][5];
//     int featurePosCount[n_features][5];
//     float featureEntropy[n_features][5];

//     //set all counts to zero to begin
//     for (int i = 0; i < n_features; i++){
//         for (int j = 0; j < 5; j++){
//             featureCount[i][j] = 0;
//             featurePosCount[i][j] = 0;
//         }
//     }

//     //Calculate the positive and negative members of the set
//     for (int i = 0; i < subSet; i++){
//         temp = target[i];
//         switch(temp){
//             case 1:
//                 positiveCount++;
//             case 0:
//                 negativeCount++;
//         }
//     }
//     if (positiveCount == subSet){
//         // Return a leaf node with + label
//         Node leaf(1, "yes");
//     }
//     if (negativeCount == subSet){
//         //Return a leaf node with - label
//         Node leaf(0, "yes"); 
//     }
//     if (n_features == 0){
//         //Return a sinle node with the label = most common value for this branch
//         if (positiveCount > negativeCount){
//             //return a leaf with + label
//             Node leaf(1, "yes");
//         } else {
//             //return a leaf with - label
//             Node leaf(0, "yes");
//         }
//     }
//     ////////////////////////////////////////////////////////////////////////////
//     ///////Else, calculate the node with the highest info gain//////////////////
//     ////////////create a subNode for each value of that feature/////////////////
//     cout << "*********************************************************" << endl;
//     //Calculate the number of values for each feature.
//     for (int i = 0; i < subSet; i++){
//         for (int j = 0; j < n_features; j++){
//             //use temp to get value at dataarray[sampleNumber][featureNumber]
//             temp = dataArray[i][j]; 
//             switch (temp){  //add one to the applicable feature value
//                 case 0:
//                     featureCount[j][0]++;
//                     //if corresponding class is positive, add on to the featurePosCount
//                     if (target[i] == 1){
//                         featurePosCount[j][0]++;
//                     }
//                     break;
//                 case 1:
//                     featureCount[j][1]++;
//                     if (target[i] == 1){
//                         featurePosCount[j][1]++;
//                     }
//                     break;
//                 case 2:
//                     featureCount[j][2]++;
//                     if (target[i] == 1){
//                         featurePosCount[j][2]++;
//                     }
//                     break;
//                 case 3:
//                     featureCount[j][3]++;
//                     if (target[i] == 1){
//                         featurePosCount[j][3]++;
//                     }
//                     break;
//                 case 4:
//                     featureCount[j][4]++;
//                     if (target[i] == 1){
//                         featurePosCount[j][4]++;
//                     }
//                     break;
//                 default:
//                     break;
//             }
//         }
//     }

//     //calc the entropy for each feature value with a count
//     int featureNegCount;
//     for (int i = 0; i < n_features; i++){
//         for (int j = 0; j < 5; j++){
//             if (featureCount[i][j] <1) {break;}  // if (featureCount[i][j] == -1) {break;}  //why was this neg 0??
//             featureNegCount = featureCount[i][j] - featurePosCount[i][j];
//             featureEntropy[i][j] = attributeEntropy(featurePosCount[i][j], featureNegCount, subSet);
//         }
//     }
//     cout << "*************************************************" << endl;
    
//     //calculate the entropy for the entire set
//     float positiveE = pi(positiveCount, subSet);
//     float negativeE = pi(8, subSet);
//     float setEntropy = calcEntropy(positiveE, negativeE);
//     cout << "Entropy of set is " << setEntropy << endl;

//     //Calculating information gain and selecting the highest gain from array of gains
//     float gain[n_features];
//     float highestGain = 0;
//     int highestGainIndex;

//     for (int i = 0; i < n_features; i++){
//         gain[i] = calcInfoGain(setEntropy, featureEntropy[i][0], featureEntropy[i][1],
//                         featureEntropy[i][2], featureEntropy[i][3], featureEntropy[i][4]);
//         if (gain[i] > highestGain){
//             highestGain = gain[i];
//             highestGainIndex = i;
//         }
//     }
//     //select largest info gain
//     cout << "The highest gain is index " << highestGainIndex;
//     cout << " with a gain of: " << highestGain << endl << endl;
//     cout << "***************************************************" << endl;


//     //highest gain selected, create node using the selected attribute



////////////////////////////////////////////////////////////////////////////////////////
    //for all possible values of feature:
        //add a branch for that value
        //Let E(a) be a subset of samples which all have value a for feataure
        //if the subset E(a) is empty - 
            //add a leaf with the most common classification for value a
        //else
            //add a new subtree: IDE(E(a),Classes,FeatureSet - {Feature})
        // end if
    //end for

    return 0;
}

