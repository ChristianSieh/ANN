/******************************************************************************
* Class:	Perceptron.h
*
* Description:	Class containing the code to build and run the net based off
*				the data from the csv file, and parameter file.
*	
* Date: 2/23/2016
******************************************************************************/

#ifndef _PERCEPTRON_H
#define _PERCEPTRON_H

#include <vector>
#include <cmath>
#include "weights.h"

using namespace std;

class Perceptron
{
	public:
		double output;
		int layer;
		int node;
		float error;
		
		Perceptron();
		~Perceptron();

		void ActivationFunction(vector<float> previous_outputs, Weights wts);
};

#endif
