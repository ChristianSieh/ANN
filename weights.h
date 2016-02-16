#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

bool ReadWeightsFromFile(string weightsFile, double* &weightArray);

bool WriteWeightsToFile(string weightsFIle, double* &weightArray, vector<int> inOut);
