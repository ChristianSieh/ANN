#include "weights.h"

using namespace std;

Weights::Weights()
{

}

Weights::~Weights()
{

}

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
				tmp = -5 + rand() / double(RAND_MAX / 10);
				node_weights.push_back(tmp);
			}
			weight_layer.push_back(node_weights);
		}
		this->weights.push_back(weight_layer);
	}
}

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
}




















