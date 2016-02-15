#include "weights.h"

using namespace std;

bool ReadWeightsFromFile(string weightsFile, double* &weightArray)
{
  ifstream weights;
  int inputs = 0;
  int outputs = 0;
  string line;
  int totalWeights;

  weights.open(weightsFile.c_str());

  if(weights.is_open())
  {
    cout << "Reading from the generate weights file." << endl;
    weights >> inputs >> outputs;
    totalWeights = inputs*outputs;
    cout << "inputs: " << inputs << " outputs: " << outputs << endl;
    weights.ignore();
    weightArray = new (nothrow) double[totalWeights]();

    for(int i = 0; i < inputs * outputs; i++)
    {
      weights >> line;
      cout << "Line: " << line << endl;
      weightArray[i] = stod(line); 
    }

    if(weights >> inputs >> outputs)
    {
      cout << "more in file" << endl;
    }
    
    else
      cout << "no more in file" << endl;

    for(int l = 0; l < inputs*outputs; l++)
    {
      cout << "l: " << l << " weightArray[l]: " <<  weightArray[l] << endl;
    }
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
