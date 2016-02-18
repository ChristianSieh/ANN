#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;

bool ReadWeightsFromFile(string weightsFile, double* &weightArray);

bool WriteWeightsToFile(string weightsFIle, double* &weightArray, vector<int> nodesPerLayer);

void CreateWeights(string weightsFileName, double* &weightArray, vector<int> nodesPerLayer);

void WeightsSetUp(string weightsFileName, float learningRate, float momentum, vector<int> nodesPerLayer, double* &weightArray);
