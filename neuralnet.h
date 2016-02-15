#ifndef _NEURALNET_H
#define _NEURALNET_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "perceptron.h"
#include "prmFile.h"
#include "csvparse.h"

using namespace std;

class neuralNet
{
	public:
	vector<vector<Perceptron> > net;	

	neuralNet();
	~neuralNet();

	void buildNet(prmFile prm);
	vector<float> propogatePerceptrons(prmFile prm, vector<PDSI> csv_data, int yearIndex);
	void trainNet(prmFile prm, vector<PDSI> csv_data);
	void testNet();
	void crossValidate();
	vector<float> getInput(prmFile prm, vector<PDSI> csv_data, int yearIndex);
	float calculateError(vector<float> results);
};
#endif
