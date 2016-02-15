#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

bool ReadWeightsFromFile(string weightsFile, double* &weightArray);

bool WriteWeightsToFile(string weightsFIle, double* &weightArray, int inOut[]);
