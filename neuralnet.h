#include <iostream>
#include <vector>
#include <algorithm>
#include "perceptron.h"
#include "prmFile.h"

using namespace std;

class neuralNet
{
	public:
	vector<vector<Perceptron>> net;	

	neuralNet();
	~neuralNet();

	void buildNet(prmFile prm);
	void propogatePerceptrons();
	void trainNet(prmFile prm);
	void testNet();
	vector<float> getInput(prmFile prm, vector<PDSI> csv_data, int yearIndex);
}
