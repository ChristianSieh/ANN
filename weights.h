#ifndef _TESTWEIGHTS_H
#define _TESTWEIGHTS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "prmFile.h"

using namespace std;

class Weights
{
	public:
		vector<int> nodesPerLayer;
		vector<vector<vector<double> > > weights;

		Weights();
		~Weights();
		void WeightsSetUp(prmFile prm);
		void ReadWeightsFromFile(prmFile params);
		void WriteWeightsToFile(prmFile params);
		void CreateWeights(prmFile params);
		void PrintWeights();
};

#endif
