#include "weights.h"
#include "prmFile.h"

using namespace std;

void WeightsSetUp(prmFile prm, double* &weightArray)
{
  ifstream test;
  test.open(prm.weightsFileName.c_str());

  if(test.is_open())
  {
    test.close();
    ReadWeightsFromFile(prm.weightsFileName, weightArray);
  }
  else
  {
    CreateWeights(prm.weightsFileName, weightArray, prm.nodesPerLayer);
  }
}

void CreateWeights(string weightsFileName, double* &weightArray, vector<int> nodesPerLayer)
{
  ofstream weights;
  int layers = nodesPerLayer.size();
  int totalNodes = 0;
  int totalNodesInCurrentLayer = 0;
  int currentIndex = 0;
  double randomValue = 0;
  
  weights.open(weightsFileName);
  
  if(weights.is_open())
  {
	  srand(time(NULL));
	  if(layers > 1)
	  {
		  for(int i = 0; i < layers-1; i++)
		  {
			  totalNodes += nodesPerLayer[i] * nodesPerLayer[i+1];
		  }

		  weightArray = new(nothrow) double[totalNodes]();
		  for(int j = 0; j < totalNodes; j++)
		  {
			  randomValue = rand() % 20;
			  randomValue /= 10.00;
			  randomValue -= 1;
			  weightArray[j] = randomValue;
		  }
		  for(int i = 0; i < layers-1; i++)
		  {
			  weights << nodesPerLayer[i] << " " << nodesPerLayer[i+1] << endl;
			  totalNodesInCurrentLayer = nodesPerLayer[i] * nodesPerLayer[i+1];
			  for(int j = 0; j < totalNodesInCurrentLayer; j++)
			  {
				  weights << weightArray[currentIndex + j] << " ";
				  if((j % nodesPerLayer[i+1]) == (nodesPerLayer[i+1]-1))
				  {
					  weights << endl;
				  }
			  }
			  currentIndex += totalNodesInCurrentLayer;
			  
			  weights << endl;
		  }
		delete [] weightArray;
	  }
	  else
	  {
		cout << "Can't make an ANN with 0 or 1 layers..." << endl;  
	  }
  	weights.close();
  }
  else
  {
	cout << "ERROR: Could not open weights file to create small random weights." << endl;
    return;	
  }
}

bool ReadWeightsFromFile(string weightsFileName, double* &weightArray)
{
  ifstream weights;
  int inputs = 0;
  int outputs = 0;
  string line;
  int totalWeights = 0;
  bool firsttime = true;
  double* oldWeights;

  weights.open(weightsFileName.c_str());

  if(weights.is_open())
  {
    cout << "Reading from the generate weights file." << endl;
    
    while(weights >> inputs >> outputs)
    {
      totalWeights += inputs*outputs;
      
      if(!firsttime)
      {
        delete [] weightArray;
        weightArray = new(nothrow) double[totalWeights]();
        for(int k = 0; k < totalWeights; k++)
        {
          weightArray[k] = oldWeights[k];
        }
        for(int i = 0; i < inputs*outputs; i++)
        {
          weights >> line;
          weightArray[(totalWeights - ((inputs * outputs)-1))] = stod(line);
        }
      }

      else
      {
        weightArray = new(nothrow) double[totalWeights]();
        oldWeights = new(nothrow) double[totalWeights]();
        for(int i = 0; i < inputs * outputs; i++)
        {
          weights >> line;
          weightArray[i] = stod(line);
        }
      }

      delete [] oldWeights;
      oldWeights = new(nothrow) double[totalWeights]();
      for(int j = 0; j < totalWeights; j++)
      {
        oldWeights[j] = weightArray[j];
      }
      firsttime = false;
    } 
    delete [] oldWeights;
  }
  else
  {
    cout << "ERROR: Could not open weights file to read." << endl;
    weights.close();
    return false;
  }
  return true;
}

bool WriteWeightsToFile(string weightsFileName, double* &weightArray, vector<int> nodesPerLayer)
{
  ofstream weights;
  int layers = nodesPerLayer.size();
  int totalNodesInCurrentLayer = 0;
  int currentIndex = 0;
  
  weights.open(weightsFileName.c_str());

  if(weights.is_open())
  {
	cout << "Writing to the generated weights file." << endl;
	if(layers > 1)
    {
		for(int i = 0; i < layers-1; i++)
		{
			weights << nodesPerLayer[i] << " " << nodesPerLayer[i+1] << endl;
			totalNodesInCurrentLayer = nodesPerLayer[i] * nodesPerLayer[i+1];
			for(int j = 0; j < totalNodesInCurrentLayer; j++)
			{
				weights << weightArray[currentIndex + j] << " ";
				if((j % nodesPerLayer[i+1]) == (nodesPerLayer[i+1] - 1))
				{
					weights << endl;
				}
			}
			weights << endl;
			currentIndex+= totalNodesInCurrentLayer;
		}
	}		
	else
	{
		cout << "Can't make an ANN with 0 or 1 layers..." << endl;
	}
  }
  else
  {
	  cout << "ERRROR: Could not open weights file to write." << endl;
	  return false;
  }

  delete [] weightArray;
  return true;
}
