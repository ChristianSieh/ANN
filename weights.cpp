#include "weights.h"

using namespace std;

bool ReadWeightsFromFile(string weightsFile, double* &weightArray)
{
  ifstream weights;
  int inputs = 0;
  int outputs = 0;
  string line;
  int totalWeights = 0;
  double* oldweights;

  weights.open(weightsFile.c_str());

  if(weights.is_open())
  {
    cout << "Reading from the generate weights file." << endl;
    
    while(weights >> inputs >> outputs)
    {
      totalWeights += inputs*outputs;
      cout << "inputs: " << inputs << " outputs: " << outputs << endl;
      weights.ignore();
      
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
          weightArray[(totalWeights - (inputs * outputs))] = stod(line);
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

bool WriteWeightsToFile(string weightsFile, double* &weightArray, int inOut[])
{
  //int inOut[0] = number of input nodes.
  //int inOut[1] = number of output nodes.
  ofstream weights;
  weights.open(weightsFile.c_str());

  if(weights.is_open())
  {
    cout << "Writing to the generated weights file." << endl;
    weights << inOut[0] << " " << inOut[1] << endl;

    for(int i = 0; i < inOut[0]; i++)
    {
      for(int j = 0; j < inOut[1] - 1; j++)
      {
        weights << weightArray[j+(i*inOut[1])] << " ";
      }
      weights << weightArray[inOut[1]+(i*inOut[1])] << endl;
    }

    for(int l = 0; l < inOut[0]*inOut[1]; l++)
		{
			cout << "l: " << l << " weightArray[l]: " <<  weightArray[l] << endl;
		}
		delete[] weightArray;
  }

  for(int n = 0; n < inOut[0]*inOut[1]; n++)
  {
    cout << "n: " << n << " weightArray[n]: " <<  weightArray[n] << endl;
  }

  return true;
}
