#include "neuralnet.h"

using namespace std;

neuralNet::neuralNet(void)
{
};

neuralNet::~neuralNet(void)
{
};

void neuralNet::buildNet(prmFile prm)
{
	for(int i = 0; i < prm.layers; i++)
	{
		vector<Perceptron> layer;

		for(int j = 0; j < prm.nodesPerLayer[i]; j++)
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

void neuralNet::trainNet(prmFile prm, vector<PDSI> csv_data)
{
	int i = 0;
	float error = prm.threshold + 1;
	float errorDifference;//TODO

	while(i < prm.epochs && error > prm.threshold)
	{
		vector<int> randomIndex;

		for(int j = 0; j < csv_data.size(); j++)
		{
			randomIndex.push_back(j);
		}

		random_shuffle(randomIndex.begin(), randomIndex.end());

		for(int j = 0; j < randomIndex.size(); j++)
		{
			vector<float> results = propogatePerceptrons(prm, csv_data, randomIndex[j]);
				
			//Delta learning rule
			//wij^t+1 = wij^t (ada)yi(delta)j
			//Need to get delta
			//Adjust weights
			//Run Again
			
			
		}

		i++;
	}
}

void neuralNet::testNet()
{

}

void neuralNet::crossValidate()
{

}


vector<float> neuralNet::getInput(prmFile prm, vector<PDSI> csv_data, int yearIndex)
{
	//TODO: Check size of input vector and if to small then ignore that year	

	vector<float> inputs;

	for(int i = yearIndex; i > yearIndex - prm.yearsBurned && i >= 0; i--)
	{
		inputs.push_back(csv_data[yearIndex - i].AcresBurned);
	}		
	
	int monthsPushed = 0;
	int monthIndex = prm.endYear;

	while(monthsPushed < prm.monthsPDSI && yearIndex >= 0)
	{
		inputs.push_back(csv_data[yearIndex].DroughtIndex[monthIndex]);
	
		if(monthIndex = 0)
		{
			yearIndex--;
		}

		monthIndex = (monthIndex - 1) % 12;				
		monthsPushed++;
	}
}

float neuralNet::calculateError(vector<float> results)
{
	float error = 0;

	for( int i = 0; i < results.size(); i++)
	{
		//error += d[i] - results[i];	
	}

	error = error / results.size();

	return error;
}
