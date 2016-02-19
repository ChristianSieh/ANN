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
			per.layer = i;
			per.node = j;
			layer.push_back(per);		
		}
		
		net.push_back(layer);
	}
	
	wts.WeightsSetUp(prm);	//Build / generate weights
}


vector<vector<float> > neuralNet::propogatePerceptrons(prmFile prm, vector<PDSI> csv_data, int yearIndex)
{
	vector<vector<float> > outputs;
	outputs.push_back(getInput(prm, csv_data, yearIndex));

	//All other layers need to take the previous layers output
	for(unsigned int layer = 1; layer < net.size(); layer++)
	{
		vector<float> currentOutputs;
		for(unsigned int node = 0; node < net[layer].size(); node++)
		{	
			// Pass in [layer-1] which is the output of the prev layer
			net[layer][node].ActivationFunction(outputs[layer-1], wts);
			currentOutputs.push_back(net[layer][node].output);
			//cout << net[layer][node].output << " ";	
		}
		//cout << endl;
	
		outputs.push_back(currentOutputs);
	}

	int size = outputs.size()-1;

	//Round the results to 0 or 1
	for(unsigned int i = 0; i < outputs[size].size(); i++)
	{
		outputs[size][i] = round(outputs[size][i]);
	}

	return outputs;
}

void neuralNet::trainNet(prmFile prm, vector<PDSI> csv_data)
{
	int i = 0;
	float error = prm.threshold + 1;
	//float errorDifference;

	//TODO: Add in errorDifference so if the error isn't getting
	//lower then we quit
	while(i < prm.epochs && error > prm.threshold)
	{
		vector<int> randomIndex;

		for(unsigned int j = 0; j < csv_data.size(); j++)
		{
			randomIndex.push_back(j);
		}

		random_shuffle(randomIndex.begin(), randomIndex.end());
		//We now have our list of years to guess in random order

		for(unsigned int j = 0; j < randomIndex.size(); j++)
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
	
		if(monthIndex == 0)
		{
			yearIndex--;
		}

		monthIndex = (monthIndex - 1) % 12;				
		monthsPushed++;
	}
	
	return inputs;
}

int neuralNet::calculateGuessError(vector<int> results, vector<PDSI> csv_data, prmFile prm, int yearIndex)
{
	int error = 0;

	vector<int> desired = classify(yearIndex, csv_data, prm);

	//Should have to vectors with 3 ints each which are all 0's or 1's
	//such as 001 and 110 and then it is XOR to give us a total error
	//of 3
	for(unsigned int i = 0; i < results.size(); i++)
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
	return 0.0;
}

double neuralNet::learningRule(double weight, prmFile prm, vector<vector<float> > outputs)
{
	return 0.0;
}

//TODO: Make it so range can be dynamic
vector<int> neuralNet::classify(int yearIndex, vector<PDSI> csv_data, prmFile prm)
{
	vector<int> classified;
	
	if(csv_data[yearIndex].AcresBurned < prm.range[0])
	{
		int arr[] = {1,0,0};
		//Using vector constructor to push 3 values at once
		//might be an easier way to do this or just use
		//push back
		vector<int> temp(arr, arr+3);
		classified = temp;
	}	

	if(csv_data[yearIndex].AcresBurned > prm.range[0] && csv_data[yearIndex].AcresBurned   < prm.range[1])
	{
		int arr[] = {0,1,0};
		vector<int> temp(arr, arr+3);
		classified = temp;
	}

	if(csv_data[yearIndex].AcresBurned > prm.range[1])
	{
		int arr[] = {0,0,1};
		vector<int> temp(arr, arr+3);
		classified = temp;
	}

	return classified;
}


