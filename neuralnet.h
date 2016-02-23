#ifndef _NEURALNET_H
#define _NEURALNET_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
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
	void propogatePerceptrons(prmFile prm, csvParser csv_data, int yearIndex);
	double networkError(prmFile prm, csvParser csv_data);
	void trainNet(prmFile prm, csvParser csv_data);
	void testNet(prmFile prm, csvParser csv_data);
	void crossValidate(prmFile prm, csvParser csv_data);
	vector<float> getInput(prmFile prm, csvParser csv_data, int yearIndex);
	vector<double> calculateGuessError(csvParser csv_data, prmFile prm, int yearIndex);
	void calculateOutputNodeError(vector<double> guessError, int layer);
	void calculateHiddenNodeError(int layer);
	void learningRule(int layer, prmFile prm);
	vector<int> classify(int num, csvParser csv, prmFile prm);
};
#endif
