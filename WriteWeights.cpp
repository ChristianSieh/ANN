#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

bool WriteWeightsToFile(string weightsFile, int* &weightArray, int inOut[2])
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
