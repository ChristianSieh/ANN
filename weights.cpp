#include "weights.h"

using namespace std;

void WeightsSetUp(string weightsFileName, float learningRate, float momentum, vector<int> nodesPerLayer, double* &weightArray)
{
  ifstream test;
  test.open(weightsFileName.c_str());

  if(test.is_open())
  {
    test.close();
    ReadWeightsFromFile(weightsFileName, weightArray);
  }
  else
  {
    CreateWeights(weightsFileName, weightArray);
  }
}

void CreateWeights(string weightsFileName, double* &weightArray, vector<int> nodesPerLayer)
{
  
}

bool ReadWeightsFromFile(string weightsFileName, double* &weightArray)
{
  ifstream weights;
  int inputs = 0;
  int outputs = 0;
  string line;
  int totalWeights = 0;
  double* oldweights;

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
    cout << "Couldn't open weights file." << endl;
    weights.close();
    return false;
  }
  return true;
}

bool WriteWeightsToFile(string weightsFileName, double* &weightArray, vector<int> nodesPerLayer)
{
  //int nodesPerLayer[0] = number of input nodes.
  //int nodesPerLayer[1] = number of output nodes.
  ofstream weights;
  int loops = 0; 
  weights.open(weightsFileName.c_str());

  if(weights.is_open())
  {
    cout << "Writing to the generated weights file." << endl;
    while(loops < nodesPerLayer.size())
    {
      weights << nodesPerLayer[loops] << " " << nodesPerLayer[loops+1] << endl;

      for(int i = 0; i < nodesPerLayer[loops]; i++)
      {
        for(int j = 0; j < nodesPerLayer[loops+1] - 1; j++)
        {
          if(loops < 2)
          {
            weights << weightArray[j+(i*nodesPerLayer[loops+1])] << " ";
          }
          else
          {
            weights << weightArray[(nodesPerLayer[loops-2] * nodesPerLayer[loops-1]) + j + (i*nodesPerLayer[loops+1])] << " ";
          }
        }
        weights << endl;
      }

      loops +=2;
      weights << endl;
    }
  }

  delete [] weightArray;
  return true;
}
