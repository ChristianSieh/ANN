#ifndef _NEURALNET_H
#define _NEURALNET_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "perceptron.h"
#include "prmFile.h"
#include "csvparse.h"
#include "weights.h"

using namespace std;

class neuralNet
{
	public:
	vector<vector<Perceptron> > net;
	Weights wts;	
	Weights previousWts;

	neuralNet();
	~neuralNet();

	void buildNet(prmFile prm);
	vector<vector<float> > propogatePerceptrons(prmFile prm, vector<PDSI> csv_data, int yearIndex);
	void trainNet(prmFile prm, vector<PDSI> csv_data);
	void testNet();
	void crossValidate();
	vector<float> getInput(prmFile prm, vector<PDSI> csv_data, int yearIndex);
	vector<int> calculateGuessError(vector<float> results, vector<PDSI> csv_data, prmFile prm, int yearIndex);
	vector<float> calculateOutputNodeError(vector<int> guessError, int node, vector<float> results);
	vector<float> calculateHiddenNodeError(vector<int> guessError, int node, vector<float> results);
	void learningRule(int layer, prmFile prm, vector<vector<float> > outputs, vector<float> error);
	vector<int> classify(int num, vector<PDSI> csv_data, prmFile prm);
};
#endif
