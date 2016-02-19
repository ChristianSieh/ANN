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

	neuralNet();
	~neuralNet();

	void buildNet(prmFile prm);
	vector<vector<float> > propogatePerceptrons(prmFile prm, vector<PDSI> csv_data, int yearIndex);
	void trainNet(prmFile prm, vector<PDSI> csv_data);
	void testNet();
	void crossValidate();
	vector<float> getInput(prmFile prm, vector<PDSI> csv_data, int yearIndex);
	int calculateGuessError(vector<int> results, vector<PDSI> csv_data, prmFile prm, int yearIndex);
	float calculateOutputNodeError(int guessError, int node, vector<int> results);
	float calculateHiddenNodeError();
	double learningRule(double weight, prmFile prm, vector<vector<float> >);
	vector<int> classify(int num, vector<PDSI> csv_data, prmFile prm);
};
#endif
