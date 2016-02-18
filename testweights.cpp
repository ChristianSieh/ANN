#include "testweights.h"

using namespace std;

Weights::Weights()
{

}

Weights::~Weights()
{

}

void Weights::ReadWeights(prmFile params)
{
	ifstream fin;
	fin.open(params.weightsFileName);

	if(!fin)
	{
		printf("Could not find the weights file '%s'\n", params.weightsFileName);
		return;
	}

	//Now read in all of the 2d arrays inside the weights file, the first will be
	//nodesPerLayer[0] x nodesPerLayer[1], second will be nodesPerLayer[1] x nPL[2] ...

	for(int i = 0; i < params.layers; i++)
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

void Weights::WriteWeights(prmFile params)
{
	ofstream fout;
	fout.open(params.weightsFileName);
	
	if(!fout)
	{
		printf("Could not write to weights file '%s'\n", params.weightsFileName);
		return;
	}

	for(int i = 0; i < this->weights.size(); i++)
	{
		for(int j = 0; j < this->weights[i].size(); j++)
		{
			for(int k = 0; k < this->weights[i][j].size(); k++)
			{
				fout << this->weights[i][j][k] << " ";
			}
			fout << "\n";
		}
		fout << "\n";
	}
	fout.close();
}

void Weights::GenerateWeights(prmFile params)
{
	int temp;
	cout << "there are " << params.nodesPerLayer.size() << "layers\n";
	cin >> temp;
	srand(time(NULL));

	for(int i = 0; i < params.layers; i++)
	{
		vector<vector<double> > weight_layer;
		
		for(int j = 0; j < params.nodesPerLayer[i]; j++)
		{
			cout << "layer " << i << " has " << params.nodesPerLayer[i] << endl;
			cout << "layer " << i << " connects to " << params.nodesPerLayer[i+1] << endl;			
			vector<double> node_weights;
			for(int k = 0; k < params.nodesPerLayer[i+1]; k++)
			{
				
				double tmp;
				tmp = -1 + rand() / double(RAND_MAX / 2);
				node_weights.push_back(tmp);
			}
			weight_layer.push_back(node_weights);
		}
		cout << "added 2D array of weights\n";
		this->weights.push_back(weight_layer);
	}
}




















