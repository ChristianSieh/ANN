#include <iostream>
#include <vector>
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
}
