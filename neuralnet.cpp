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


vector<vector<float> > neuralNet::propogatePerceptrons(prmFile prm, vector<PDSI> csv_data, int yearIndex)
{

	vector<vector<float> > outputs.push_back(getInput(prm, csv_data, yearIndex));

	//All other layers need to take the previous layers output
	for(int i = 1; i < net.size(); i++)
	{
		vector<float> currentOutputs;
		for(int j = 0; j< net[i].size(); j++)
		{	
			net[i][j].ActivationFunction(previousOutputs, j);
			currentOutputs.push_back(net[i][j].output);	
		}
	
		outputs.push_back(currentOutputs);
	}

	int size = outputs.size();

	//Round the results to 0 or 1
	for(int i = 0; i < outputs[size].size(); i++)
	{
		outputs[size][i] = round(outputs[size][i]);
	}

	return outputs;
}

void neuralNet::trainNet(prmFile prm, vector<PDSI> csv_data)
{
	int i = 0;
	float error = prm.threshold + 1;
	float errorDifference;

	//TODO: Add in errorDifference so if the error isn't getting
	//lower then we quit
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
			vector<vector<float> > outputs = propogatePerceptrons(prm, csv_data, randomIndex[j]);
			
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

int neuralNet::calculateGuessError(vector<int> results, vector<PDSI> csv_data, prmFile prm, int yearIndex)
{
	int error = 0;

	vector<int> desired = classify(yearIndex, prm)

	//Should have to vectors with 3 ints each which are all 0's or 1's
	//such as 001 and 110 and then it is XOR to give us a total error
	//of 3
	for(int i = 0; i < results.size(); i++)
	{
		error += desired[i] ^ results[i];	
	}

	return error;
}

float neuralNet::calculateOutputNodeError(int guessError, int node, vector<int> results)
{
	return results[node] * (1 - results[node]) * guessError;
}

float neuralNet::calculateHiddenNodeError()
{
	
}

double neuralNet::learningRule(double weight, prmFile prm, vector<vector<float> >)
{
	
}

//TODO: Make it so range can be dynamic
vector<int> neuralNet::classify(int yearIndex, vector<PDSI> csv_data, prmFile prm)
{
	vector<int> classified;
	
	if(csv_data[yearIndex].AcresBurned < prm.range[0])
	{
		int arr[] = {1,0,0}
		classified.push_back(arr, arr+3);
	}	

	if(csv_data[yearIndex].AcresBurned > prm.range[0] && csv_data[yearIndex].AcresBurned   < prm.range[1])
	{
		int arr[] = {0,1,0}
		classified.push_back(arr, arr+3);
	}

	if(csv_data[yearIndex].AcresBurned > prm.range[1])
	{
		int arr[] = {0,0,1}
		classified.push_back(arr, arr+3);
	}

	return classified;
}


