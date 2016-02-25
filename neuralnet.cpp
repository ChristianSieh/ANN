/******************************************************************************
* File: 	neuralnet.cpp
*
* Authors: 	Jason Anderson, Dylan Geyer, and Christian Sieh
*
* Description: 	This file contains the implementation of neuralnet. It
*		implements the constructor/destructor, and its associated functions.
*
* Date: 	2/21/2016
******************************************************************************/

#include "neuralnet.h"

using namespace std;

/******************************************************************************
* Function:	neuralNet
*
* Description:	Constructor for neuralNet class, unused.
*
* Parameters:	none
*
* Returns:	none
******************************************************************************/

neuralNet::neuralNet(void)
{
};

/******************************************************************************
* Function:	~neuralNet
*
* Description:	Deconstructor for neuralNet class, unused.
*
* Parameters:	none
*
* Returns:	none
******************************************************************************/

neuralNet::~neuralNet(void)
{
};

/******************************************************************************
* Function:	buildNet
*
* Description:	Creates the net.
*
* Parameters:	prmFile prm, weights from the wts file.
*
* Returns:	none
******************************************************************************/

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

/******************************************************************************
* Function:	propogatePerceptrons
*
* Description:	This function feeds forward through the entire net in order to
*		obtain an output (guess).
*
* Parameters:	prmFile prm, csvParser csv_data, int yearIndex
*
* Returns:	none
******************************************************************************/

bool neuralNet::propogatePerceptrons(prmFile prm, csvParser csv_data, int yearIndex)
{
	vector<vector<float> > outputs;
	outputs.push_back(getInput(prm, csv_data, yearIndex));
	
	if(outputs[outputs.size()-1].size() == 0)
	{
		return true;
	}

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
				net[layer][node].ActivationFunction(outputs[layer-1], wts);
				currentOutputs.push_back(net[layer][node].output);
			}
		}

		// Don't push the outputs of the input layer
		if(layer == 0)
			continue;

		outputs.push_back(currentOutputs);
	}
	return false;
}

/******************************************************************************
* Function:	trainNet
*
* Description:	Trains the net.
*
* Parameters:	prmFile prm, csvParser csv_data
*
* Returns:	none
******************************************************************************/

void neuralNet::trainNet(prmFile prm, csvParser csv_data)
{
	int i = 0;
	float error = prm.threshold + 1;

	while(i < prm.epochs && error > prm.threshold)
	{	
		vector<int> randomIndex;

		for(unsigned int j = 0; j < csv_data.csv_data.size(); j++)
		{
			randomIndex.push_back(j);
		}

		random_shuffle(randomIndex.begin(), randomIndex.end());

		vector<double> guessError;

		for(unsigned int j = 0; j < randomIndex.size(); j++)
		{
			propogatePerceptrons(prm, csv_data, randomIndex[j]);
					
			for(unsigned int layer = net.size() - 1; layer > 0; layer--)
			{
				if(layer == net.size() - 1)
				{
					guessError = calculateGuessError(csv_data, prm, randomIndex[j]);
					calculateOutputNodeError(guessError, layer);
				}
				else
				{ 
					calculateHiddenNodeError(layer);
				}				

				learningRule(layer, prm);
			}						
		}
		if(i % 10 == 0)
		{
			error = networkError(prm, csv_data);
			error = sqrt(error);
			cout << "Epoch: " << i << "   " << setprecision(3) << error << endl;
		}
		i++;
	}
}

/******************************************************************************
* Function:	networkError
*
* Description:	Calculates the network error.
*
* Parameters:	prmFile prm, csvParser csv_data
*
* Returns:	summation / networkError.size()
******************************************************************************/

double neuralNet::networkError(prmFile prm, csvParser csv_data)
{
	vector<double> networkError;

	for(unsigned int i = 0; i < csv_data.csv_data.size(); i++)
	{
		propogatePerceptrons(prm, csv_data, i);
	
		vector<double> guessError = calculateGuessError(csv_data, prm, i);

		double temp = 0;
		for(unsigned int j = 0; j < guessError.size(); j++)
		{
			temp += abs(guessError[j]);
		}
		networkError.push_back(temp / guessError.size());
	}

	double summation = 0;

	for(unsigned int i = 0; i < networkError.size(); i++)
	{
		summation += pow(networkError[i], 2);
	}
	
	return summation / networkError.size();
}

/******************************************************************************
* Function:	testNet
*
* Description:	Tests the net.
*
* Parameters:	prmFile prm, csvParser csv_data
*
* Returns:	none
******************************************************************************/

void neuralNet::testNet(prmFile prm, csvParser csv_data)
{
	int numWrong = 0;
	bool minimalData = false;
	int minimalCount = 0;

	cout << "Sample,  Desired, Actual " << endl;

	for(unsigned int i = 0; i < csv_data.csv_data.size(); i++)
	{
		vector<int> guess;
		
		minimalData = propogatePerceptrons(prm, csv_data, i);

		int size = net.size() - 1;

		for(unsigned int j = 0; j < net[size].size(); j++)
		{
			guess.push_back(round(net[size][j].output));
		}

		vector<int> desired = classify(i, csv_data, prm);
	
		if(!minimalData)
		{	
			cout << i - minimalCount << ", ";

			for(unsigned int j = 0; j < desired.size(); j++)
			{
				cout << desired[j];
			}

			cout << ", ";

			for(unsigned int j = 0; j < desired.size(); j++)
			{
				cout << guess[j];
			}

			bool incorrect = false;

			for(unsigned int j = 0; j < desired.size(); j++)
			{
				if(desired[j] != guess[j] && incorrect != true)
				{
				incorrect = true;
				numWrong++;				
			}
			}

			if(incorrect)
				cout << '*';
		
			cout << endl;
		}
		else
			minimalCount++;
	}

	cout << "numWrong: " << numWrong << endl;
	cout << "csv_data.size(): " << csv_data.csv_data.size() - minimalCount << endl;
	cout << "Percentage: " << 100 - ((double(numWrong)/csv_data.csv_data.size()) * 100) << endl;
}

/******************************************************************************
* Function:	crossValidate
*
* Description:	Cross Validates the data in the file.  Takes 1 year of data out,
*				trains it on the rest, then tests it on the year taken out.
*
* Parameters:	prmFile prm, csvParser csv_data
*
* Returns:	none
******************************************************************************/

void neuralNet::crossValidate(prmFile prm, csvParser csv_data)
{
	int i = 0;
	int numWrong = 0;
	int minimalData = false;
	int minimalCount = 0;
	float error = prm.threshold + 1;
	
	cout << "Sample, Desired, Actual" << endl;

	//#pragma omp parallel for
	for(unsigned int j = 0; j < csv_data.csv_data.size(); j++)
	{
		wts.CreateWeights(prm);
		while(i < prm.epochs && error > prm.threshold)
		{
			vector<int> randomIndex;
			
			for(unsigned int k = 0; k < csv_data.csv_data.size(); k++)
			{
				if(k != j)
					randomIndex.push_back(k);
			}

			random_shuffle(randomIndex.begin(), randomIndex.end());

			vector<double> guessError;

			for(unsigned int k = 0; k < randomIndex.size(); k++)
			{
				propogatePerceptrons(prm, csv_data, randomIndex[k]);
				
				for(unsigned int layer = net.size() - 1; layer > 0; layer--)
				{
					if(layer == net.size() - 1)
					{
						guessError = calculateGuessError(csv_data, prm, randomIndex[k]);
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
		
		vector<int> guess;
		minimalData = propogatePerceptrons(prm, csv_data, j);
		int size = net.size() - 1;

		for(unsigned int l = 0; l < net[size].size(); l++)
		{
			guess.push_back(round(net[size][l].output));
		}

		vector<int> desired = classify(j, csv_data, prm);

		if(!minimalData)
		{
			cout << j << ", ";

			for(unsigned int l = 0; l < desired.size(); l++)
			{
				cout << desired[l];
			}

			cout << ", ";

			for(unsigned int l = 0; l < desired.size(); l++)
			{
				cout << guess[l];
			}
	
			bool incorrect = false;

			for(unsigned int l = 0; l < desired.size(); l++)
			{
				if(desired[l] != guess[l] && incorrect != true)
				{
					incorrect = true;
					numWrong++;
				}
			}
		
			if(incorrect)
				cout << "*";
	
			cout << endl;
		}
		else
			minimalCount++;

		i = 0;
	}
	cout << "numWrong: " << numWrong << endl;
	cout << "csv_data.size(): " << csv_data.csv_data.size() << endl;
	cout << "Percentage: " << 100 - ((double(numWrong)/csv_data.csv_data.size())*100) << endl;
}

/******************************************************************************
* Function:	getInput
*
* Description:	Builds input feature vector from csv data.
*
* Parameters:	prmFile prm, csvParser csv_data, int yearIndex
*
* Returns:	vector of floats the size of the input layer / feature vector)
******************************************************************************/

vector<float> neuralNet::getInput(prmFile prm, csvParser csv_data, int yearIndex)
{
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

		monthIndex--;
		if(monthIndex < 0)
			monthIndex = 11;

		monthsPushed++;
	}
	
	//Push bias input to the input vector, this value is large because we always want
	//bias node to output ~= 1.0
	inputs.push_back(1);
	
	if(inputs.size() != unsigned (prm.nodesPerLayer[0]))
	{
		inputs.clear();
	}
	return inputs;
}

/******************************************************************************
* Function:	calculateGuessError
*
* Description:	calculates the guess error.
*
* Parameters:	csvParser csv_data, prmFile prm, int yearIndex
*
* Returns:	vector<double> error
******************************************************************************/

vector<double> neuralNet::calculateGuessError(csvParser csv_data, prmFile prm, int yearIndex)
{
	vector<double> error;

	vector<int> desired = classify(yearIndex, csv_data, prm);
	
	int size = net.size() - 1;

	for(unsigned int i = 0; i < net[size].size(); i++)
	{
		double test = desired[i] - net[size][i].output;
		error.push_back(test);	
	}

	return error;
}

/******************************************************************************
* Function:	calculateOutputNodeError
*
* Description:	calculates the output node error.
*
* Parameters:	vector<double> guessError,  int layer
*
* Returns:	none
******************************************************************************/

//Delta(k)
void neuralNet::calculateOutputNodeError(vector<double> guessError,  int layer)
{
	for(unsigned int i = 0; i < net[layer].size(); i++)
	{
		net[layer][i].error = (net[layer][i].output * (1 - net[layer][i].output) * guessError[i]);
	}
}

/******************************************************************************
* Function:	calculateOutputNodeError
*
* Description:	calculates the hidden node error.
*
* Parameters:	int layer
*
* Returns:	none
******************************************************************************/

//Delta(j)
void neuralNet::calculateHiddenNodeError(int layer)
{
	//Get the summation of wjk * delta(k)
	for(unsigned int node = 0; node < net[layer].size(); node++)
	{
		float summation = 0;
			
		for(unsigned int k = 0; k < net[layer + 1].size(); k++)
		{
			summation += wts.weights[layer][node][k] * net[layer + 1][k].error;			
		}		

		float yj = net[layer][node].output;		
		
		net[layer][node].error = yj * (1 - yj) * summation;

	}
}

/******************************************************************************
* Function:	learning rule
*
* Description:	Implements the neural net learning rule.
*
* Parameters:	int layer, prmFile prm
*
* Returns:	none
******************************************************************************/

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
			wts.weights[layer - 1][j][i] += prm.learningRate * net[layer - 1][j].output * net[layer][i].error;

		}	
	}
}

/******************************************************************************
* Function:	classify
*
* Description:	classifies the year to the output nodes in the neural net.
*
* Parameters:	int yearIndex, csvParser csv, prmFile prm
*
* Returns:	classified
******************************************************************************/
vector<int> neuralNet::classify(int yearIndex, csvParser csv, prmFile prm)
{
	vector<int> classified;
	bool isClassified = false;
	unsigned int i = 0;

	while(i < prm.range.size() && isClassified == false)
	{
		if(csv.csv_data[yearIndex].AcresBurned * csv.maxBurnedAcre < prm.range[i])
		{
			for(unsigned int j = 0; j <= prm.range.size(); j++)
			{
				if(j == i)
					classified.push_back(1);
				else
					classified.push_back(0);
			}
			isClassified = true;
		}

		if(i == prm.range.size()- 1 && csv.csv_data[yearIndex].AcresBurned * csv.maxBurnedAcre > prm.range[i])
		{
			for(unsigned int j = 0; j <= prm.range.size(); j++)
			{
				if(j == i + 1)
					classified.push_back(1);
				else
					classified.push_back(0);
			}		
			isClassified = true;
		}
	
		i++;	
	}
	
	return classified;
}


