#include <vector>

using namespace std;

Perceptron::Perceptron(void)
{

}

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
Perceptron::void ActivationFunction(vector<float> previous_outputs, int node)
{
	//Look at the weights of each output to calculate the Sum(Wij * Yij)
	//1 / (1-e^-x)
}

