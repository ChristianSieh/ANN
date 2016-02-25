/******************************************************************************
* File:		weights.cpp
*
* Authors: 	Dylan Geyer, Jason Anderson
*
* Description: 	This file contains a class definition for the class weights.
*		This class contains 4 functions, CreateWeights, ReadWeightsFromFile, 
*		WriteWeightsToFile, and the helper function WeightsSetUp.
*
* Date: 	2/21/2016
******************************************************************************/

#include "weights.h"

using namespace std;

/******************************************************************************
* Function:	weights
*
* Description:	Constructor for weights class, unsued.
*
* Parameters:	none
*
* Returns:	none
******************************************************************************/

Weights::Weights()
{

}

/******************************************************************************
* Function:	~Weights
*
* Description:	Constructor for weights class, unsued.
*
* Parameters:	none
*
* Returns:	none
******************************************************************************/

Weights::~Weights()
{

}

/******************************************************************************
* Function:	WeightsSetUp
*
* Description:	Tests to see if the file exists to read from.  If not then calls
*				CreateWeights to create a new file and generate file.
*
* Parameters:	prmFile prm
*
* Returns:	none
******************************************************************************/

void Weights::WeightsSetUp(prmFile prm)
{
	ifstream test;
	test.open(prm.weightsFileName);
	
	if(test.is_open())
	{
		test.close();
		ReadWeightsFromFile(prm);
	}
	else
	{
		CreateWeights(prm);
	}
}

/******************************************************************************
* Function:	ReadWeightsFromFile
*
* Description:	Opens the wts file and reads the weights into a 3d vector 
*               of doubles.
*
* Parameters:	prmFile params
*
* Returns:	weight_layer
******************************************************************************/

void Weights::ReadWeightsFromFile(prmFile params)
{
	ifstream fin;
	fin.open(params.weightsFileName);

	//Now read in all of the 2d arrays inside the weights file, the first will be
	//nodesPerLayer[0] x nodesPerLayer[1], second will be nodesPerLayer[1] x nPL[2] ...

	for(int i = 0; i < params.layers-1; i++)
	{
		vector<vector<double> > weight_layer;
		
		for(int j = 0; j < params.nodesPerLayer[i]; j++)
		{
			vector<double> node_weights;
			for(int k = 0; k < params.nodesPerLayer[i+1]; k++)
			{
				double tmp;
				fin >> tmp;
				node_weights.push_back(tmp);
			}
			weight_layer.push_back(node_weights);
		}
		this->weights.push_back(weight_layer);
	}
	fin.close();
}

/******************************************************************************
* Function:	WriteWeightsToFile
*
* Description:	Writes the weights to the wts file.
*
* Parameters:	prmFile params, vector weights
*
* Returns:	none
******************************************************************************/

void Weights::WriteWeightsToFile(prmFile params)
{
	ofstream fout;
	fout.open(params.weightsFileName);
	
	if(!fout)
	{
		printf("Could not write to weights file '%s'\n", params.weightsFileName.c_str());
		return;
	}

	for(unsigned int i = 0; i < this->weights.size(); i++)
	{
		for(unsigned int j = 0; j < this->weights[i].size(); j++)
		{
			for(unsigned int k = 0; k < this->weights[i][j].size(); k++)
			{
				fout << this->weights[i][j][k] << " ";
			}
			fout << "\n";
		}
		fout << "\n";
	}
	fout.close();
}

/******************************************************************************
* Function:	CreateWeights
*
* Description:	Creates new weights between -.1 and .1 saves it in a 2d vector.
*
* Parameters:	prmFile params
*
* Returns:	weight_layer
******************************************************************************/

void Weights::CreateWeights(prmFile params)
{
	srand(time(NULL));

	for(int i = 0; i < params.layers-1; i++)
	{
		vector<vector<double> > weight_layer;
		
		for(int j = 0; j < params.nodesPerLayer[i]; j++)
		{			
			vector<double> node_weights;
			for(int k = 0; k < params.nodesPerLayer[i+1]; k++)
			{
				
				double tmp;
				// Best results using the range (-0.1 to +0.1)
				tmp = -.1 + rand() / double(RAND_MAX / .2);
				node_weights.push_back(tmp);
			}
			weight_layer.push_back(node_weights);
		}
		this->weights.push_back(weight_layer);
	}
}

/*
void Weights::PrintWeights()
{
	for(unsigned int i = 0; i < weights.size(); i++)
	{

		for(unsigned int j = 0; j < weights[i].size(); j++)
		{
			for(unsigned int k = 0; k < weights[i][j].size(); k++)
			{
				cout << weights[i][j][k] << " "; 
			}
			cout << endl;
		}
		cout << endl;
	}
}*/




















