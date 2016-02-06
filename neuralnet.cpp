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


vector<float> neuralNet::propogatePerceptrons(prmFile prm, vector<PDSI> csv_data, int yearIndex)
{

	vector<float> previousOutputs = getInput(prm, csv_data, yearIndex);

	//All other layers need to take the previous layers output
	for(int i = 1; i < net.size(); i++)
	{
		vector<float> currentOutputs;
		for(int j = 0; j< net[i].size(); j++)
		{	
			net[i][j].ActivationFunction(previousOutputs, j);
			currentOutputs.push_back(net[i][j].output);	
		}
	
		previousOutputs = currentOutputs;
	}

	return previousOutputs;
}

void neuralNet::trainNet(prmFile prm, vector<PDSI> csv_data, int yearIndex)
{
	vector<int> randomIndex;

	for(int i = 0; i < csv_data.size(); i++)
	{
		randomIndex.push_back(i);
	}

	random_shuffle(randomIndex.begin(), randomIndex.end());

	for(int i = 0; i < randomIndex.size(); i++)
	{
		vector<float> results = propogatePerceptrons(prm, csv_data, randomIndex[i]);
			
		//Delta learning rule
		//wij^t+1 = wij^t (ada)yi(delta)j
		//Need to get delta
		//Adjust weights
		//Run Again
		
	}
}

void neuralNet::testNet()
{

}

vector<float> neuralnet::getInput(prmFile prm, vector<PDSI> csv_data, int yearIndex)
{
	vector<float> inputs;

	for(int i = yearIndex; i > yearIndex - prm.yearsBurned && i >= 0; i--)
	{
		inputs.push_back(csv_data[yearIndex - i);
	}		
	
	int monthsPushed = 0;
	int monthIndex = prm.endYear;

	while(monthsPushed < monthsPDSI && yearIndex >= 0)
	{
		inputs.push_back(csv_data[yearIndex].DroughtIndex[monthIndex];
	
		if(monthIndex = 0)
		{
			yearIndex--;
		}

		monthIndex = (monthIndex - 1) % 12;				
		monthsPushed++;
	}
}
