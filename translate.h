#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <tuple>
#include "dataClasses.h"
#include "helperFunctions.h"
#include "functions.h"

using namespace std;


#ifndef TRANSLATE_H
#define TRANSLATE_H

ReferenceTable translator();

void translate(ReferenceTable table, string fileName);



#endif //TRANSLATE_H
