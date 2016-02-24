/******************************************************************************
* File: 	percepton.cpp
*
* Authors:  
*
* Description: 	This file contains the implementation of perceptron. It
*		implements the constructor/destructor, and the activation function.
*
* Date: 	2/21/2016
******************************************************************************/

#include "perceptron.h"
#include "weights.h"

using namespace std;

/******************************************************************************
* Function:	Perceptron
*
* Description:	Constructor for percepton class, unsued.
*
* Parameters:	none
*
* Returns:	none
******************************************************************************/

Perceptron::Perceptron(void)
{

}

/******************************************************************************
* Function:	~Perceptron
*
* Description:	Deconstructor for percepton class, unsued.
*
* Parameters:	none
*
* Returns:	none
******************************************************************************/

Perceptron::~Perceptron(void)
{

}

/******************************************************************************
* Function:	ActivationFunction
* 
* Description:	This function receives a list of output values that are coming
*				into the percepton and its location in its layer. This must be
*				given so that the perceptron knows which column in the weight
*				array to elementwise multiply the previous_outputs with.
*
* Parameters:	previous_outputs - Contains all outputs from the previous layer
*				node - This perceptrons position in the current layer
******************************************************************************/
void Perceptron::ActivationFunction(vector<float> previous_output, Weights wts)
{
	if(layer < 1)
	{
		output = previous_output[node];
		return;
	}

	//Look at the weights of each output to calculate x = Sum(Wij * Yi) then
	//output = 1 / (1-e^-x)
	double x = 0;
	for(unsigned int i = 0; i < previous_output.size(); i++)
	{
		// i corresponds to the node num in previous node layer
		x += previous_output[i] * wts.weights[layer-1][i][node];
	}

	output = 1.0 / (1.0 + exp(-x));
}

