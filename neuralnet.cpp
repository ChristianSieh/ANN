#include "neuralnet.h"
#include "perceptron.h"

using namespace std;

neuralNet::net(void)
{
};

neuralNet::~net(void)
{
};

void neuralNet::buildNet(prmFile prm)
{
	for(int i = 0; i < prm.layers.size(); i++)
	{
		vector<Perceptron> layer;

		for(int j = 0; j < prm.nodesPerLayer[i].size(); j++)
		{
			Perceptron per;
			layer.push_back(per);		
		}
		
		net.push_back(layer);
	}
}


void neuralNet::propogatePerceptrons(vector<PDSI> csv_data)
{
	vector<float> previousOutputs;

	//Input layer need to pass in inputs from csvFile
	for(int j = 0; j < net[0].size(); j++)
	{
		net[0][j].ActivationFunction(inputs, j);
	}

	//All other layers need to take the previous layers output
	for(int i = 1; i < net.size(); i++)
	{
		for(int j = 0; j< net[i].size(); j++)
		{
			net[i][j].ActivationFunction(previousOutputs, j);
		}
	}
}

void neuralNet::trainNet(prmFile prm)
{

}
