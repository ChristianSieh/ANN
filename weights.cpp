#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

bool ReadWeightsFromFile(string weightsFile, int* &weightArray)
{
  ifstream weights;
  int inputs = 0;
  int outputs = 0;
  string line;
  int space = 0;
  int power = -1;

  weights.open(weightsFile.c_str());

  if(weights.is_open())
  {
    cout << "Reading from the generate weights file." << endl;
    weights >> inputs >> outputs;
    cout << "inputs: " << inputs << " outputs: " << outputs << endl;
    weights.ignore();
    weightArray = new (nothrow) int[inputs*outputs]();

    for(int i = 0; i < inputs; i++)
    {
      getline(weights, line);

      for(int j = 0; j < line.length(); j++)
      {
        space = line.find_first_of(" ");
        for(int k = space - 1; k >= 0; k--)
	{
          power++;
          cout << "line[k]: " <<  line[k] << endl;
	  weightArray[j+(i*outputs)] += atoi(line[k]) * pow(10,power);
	}
        power = -1;

	line.erase(0, space + 1);

	if(space == -1)
	{
          for(int m = line.length() - 1; m >= 0; m--)
          {
            power++;
            if(j == 0)
            {					  
              weightArray[j+(i*outputs)] += (line[m] - 48)*pow(10, power);
            }
            else
            {
              weightArray[j+(i*outputs)] += (line[m] - 48)*pow(10, power);
            }
          }
          power = -1;
          break;
	}
		
	j = 0;
        if(line.length() == 1)
        {
          weightArray[j+(i*outputs)+1] = line[0] - 48;
        }
      }
    }

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
