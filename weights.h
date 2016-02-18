#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>
#include "prmFile.h"

using namespace std;

bool ReadWeightsFromFile(string weightsFileName, double* &weightArray);

bool WriteWeightsToFile(string weightsFileName, double* &weightArray, vector<int> nodesPerLayer);

void CreateWeights(string weightsFileName, double* &weightArray, vector<int> nodesPerLayer);

void WeightsSetUp(prmFile prm, double* &weightArray);
