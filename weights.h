/******************************************************************************
* File:		weights.h
*
* Authors: 	Jason Anderson
*
* Description: 	This file contains a class definition for the class weights.
*		This class reads and writes the weights needed for the ANN.
*
* Date: 	2/23/2016
******************************************************************************/

#ifndef _TESTWEIGHTS_H
#define _TESTWEIGHTS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "prmFile.h"

using namespace std;

/******************************************************************************
* Class:	Weights
*
* Description:	Class containing the code for implementing the use and storage
*				of weights.
*	
******************************************************************************/

class Weights
{
	public:
		vector<int> nodesPerLayer;
		vector<vector<vector<double> > > weights;

		Weights();
		~Weights();
		void WeightsSetUp(prmFile prm);
		void ReadWeightsFromFile(prmFile params);
		void WriteWeightsToFile(prmFile params);
		void CreateWeights(prmFile params);
		void PrintWeights();
};

#endif
