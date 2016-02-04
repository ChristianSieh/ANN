#include <vector>

using namespace std;

class Perceptron
{
	public:
		float output;
		
		Perceptron();
		~Perceptron();

		void ActivationFunction(vector<float> previous_outputs, int node);
};
