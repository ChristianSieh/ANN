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
