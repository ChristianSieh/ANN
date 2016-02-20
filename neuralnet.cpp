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
	previousWts = wts;
}


void neuralNet::propogatePerceptrons(prmFile prm, csvParser csv_data, int yearIndex)
{
	vector<vector<float> > outputs;
	outputs.push_back(getInput(prm, csv_data, yearIndex));

	//All other layers need to take the previous layers output
	for(unsigned int layer = 0; layer < net.size(); layer++)
	{
		vector<float> currentOutputs;
		for(unsigned int node = 0; node < net[layer].size(); node++)
		{	
			if(layer == 0)
			{
				net[layer][node].ActivationFunction(outputs[layer], wts);
			}
			else
			{
				// Pass in [layer-1] which is the output of the prev layer
				net[layer][node].ActivationFunction(outputs[layer-1], wts);
				currentOutputs.push_back(net[layer][node].output);
				//cout << "Node Output: " << net[layer][node].output << " ";	
			}
		}
		//cout << endl;
	
		outputs.push_back(currentOutputs);
	}

	//int size = net.size()-1;

	//Round the results to 0 or 1
/*	for(unsigned int i = 0; i < net[size].size(); i++)
	{
//		cout << "Output Node" << i << " " << net[size][i].output << endl;
		net[size][i].output = round(net[size][i].output);
//		cout << "Output Node After" << i << " " << net[size][i].output << endl;
	}*/
}

void neuralNet::trainNet(prmFile prm, csvParser csv_data)
{
	int i = 0;
	float error = prm.threshold + 1;
	//float errorDifference;

	//TODO: Add in errorDifference so if the error isn't getting
	//lower then we quit
	while(i < prm.epochs && error > prm.threshold)
	{
		//cout << "Epochs: " << i << endl;
	
		vector<int> randomIndex;

		for(unsigned int j = 0; j < csv_data.csv_data.size(); j++)
		{
			randomIndex.push_back(j);
		}

		random_shuffle(randomIndex.begin(), randomIndex.end());
		//We now have our list of years to guess in random order

		for(unsigned int j = 0; j < randomIndex.size(); j++)
		{
			propogatePerceptrons(prm, csv_data, randomIndex[j]);
			
			vector<double> guessError = calculateGuessError(csv_data, prm, randomIndex[j]);
		
			for(unsigned int layer = net.size() - 1; layer > 0; layer--)
			{
				if(layer == net.size() - 1)
				{
					calculateOutputNodeError(guessError, layer);
				}
				else
				{ 
					calculateHiddenNodeError(layer);
				}				

				learningRule(layer, prm);
			}						
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


vector<float> neuralNet::getInput(prmFile prm, csvParser csv_data, int yearIndex)
{
	//TODO: Check size of input vector and if to small then ignore that year	

	vector<float> inputs;

	for(int i = yearIndex; i > yearIndex - prm.yearsBurned && i >= 0; i--)
	{
		inputs.push_back(csv_data.csv_data[yearIndex - i].AcresBurned);
	}		
	
	int monthsPushed = 0;
	int monthIndex = prm.endYear;

	while(monthsPushed < prm.monthsPDSI && yearIndex >= 0)
	{
		inputs.push_back(csv_data.csv_data[yearIndex].DroughtIndex[monthIndex]);
	
		if(monthIndex == 0)
		{
			yearIndex--;
		}

		monthIndex = (monthIndex - 1) % 12;				
		monthsPushed++;
	}
	
	return inputs;
}

vector<double> neuralNet::calculateGuessError(csvParser csv_data, prmFile prm, int yearIndex)
{
	vector<double> error;

	vector<int> desired = classify(yearIndex, csv_data, prm);

	//Should have to vectors with 3 ints each which are all 0's or 1's
	//such as 001 and 110 and then it is XOR to give us a total error
	//of 3
	
	int size = net.size() - 1;

	for(unsigned int i = 0; i < net[size].size(); i++)
	{
		//TODO:Make sure this works
		//Changed this from XOR
		double test = desired[i] - net[size][i].output;
		error.push_back(test);	
		cout << "TEST: " << test << endl;
	}

	return error;
}

//Delta(k)
void neuralNet::calculateOutputNodeError(vector<double> guessError,  int layer)
{
	for(unsigned int i = 0; i < net[layer].size(); i++)
	{
		cout << "BEFORE Output Error: " << net[layer][i].error << endl;
		net[layer][i].error = (net[layer][i].output * (1 - net[layer][i].output) * guessError[i]);
		cout << "AFTER Output Error: " << net[layer][i].error << endl;
	}
}

//Delta(j)
void neuralNet::calculateHiddenNodeError(int layer)
{
	//Get the summation of wjk * delta(k)
	for(unsigned int node = 0; node < net[layer].size(); node++)
	{
		float summation = 0;
	
		//cout << "BEFORE Error: " << net[layer][node].error << endl;
			
		for(unsigned int k = 0; k < net[layer + 1].size(); k++)
		{
			cout << "Weights: " << wts.weights[layer][node][k] << endl;
			cout << "Error: " << net[layer + 1][k].error << endl;
			summation += wts.weights[layer][node][k] * net[layer + 1][k].error;			
		}		

		float yj = net[layer][node].output;		
		
		net[layer][node].error = yj * (1 - yj) * summation;
		//cout << "Summation: " << summation << endl;
		//cout << "YJ: " << yj << endl;
		//cout << "AFTER Error: " << net[layer][node].error << endl;
	}
}

//Given a layer it should adjust the weights between the given layer and the previous layer.
//For node k in layer iterate through all the weights from k through all the nodes in layer j (the previous layer).
//
void neuralNet::learningRule(int layer, prmFile prm)
{
	// i iterates through nodes in layer
	for(unsigned int i = 0; i < net[layer].size(); i++)
	{
		// j iterates through nodes in layer-1
		for(unsigned int j = 0; j < net[layer - 1].size(); j++)
		{
			//cout << "BEFORE LearningRate: " << prm.learningRate << " Node Output: " << net[layer-1][j].output << " Error: " << net[layer][i].error << endl;
			wts.weights[layer - 1][j][i] += prm.learningRate * net[layer - 1][j].output * net[layer][i].error;
			//cout << "AFTER LearningRate: " << prm.learningRate << " Node Output: " << net[layer-1][j].output << " Error: " << net[layer][i].error << endl;
		}	
	}
}

//TODO: Make it so range can be dynamic
vector<int> neuralNet::classify(int yearIndex, csvParser csv, prmFile prm)
{
	vector<int> classified;

	cout << "AcresBurned: " << csv.csv_data[yearIndex].AcresBurned * csv.maxBurnedAcre << " Range: " << prm.range[0] << " " << prm.range[1] << " YearIndex: " << yearIndex << endl;
	
	if(csv.csv_data[yearIndex].AcresBurned * csv.maxBurnedAcre < prm.range[0])
	{
		int arr[] = {1,0,0};
		//Using vector constructor to push 3 values at once
		//might be an easier way to do this or just use
		//push back
		vector<int> temp(arr, arr+3);
		classified = temp;
		cout << "Classified1: " << classified[0] << classified[1] << classified[2] << endl;
	}	

	if(csv.csv_data[yearIndex].AcresBurned * csv.maxBurnedAcre > prm.range[0] && csv.csv_data[yearIndex].AcresBurned * csv.maxBurnedAcre   < prm.range[1])
	{
		int arr[] = {0,1,0};
		vector<int> temp(arr, arr+3);
		classified = temp;
		cout << "Classified2: " << classified[0] << classified[1] << classified[2] << endl;
	}

	if(csv.csv_data[yearIndex].AcresBurned * csv.maxBurnedAcre > prm.range[1])
	{
		int arr[] = {0,0,1};
		vector<int> temp(arr, arr+3);
		classified = temp;
		cout << "Classified3: " << classified[0] << classified[1] << classified[2] << endl;
	}

	return classified;
}


