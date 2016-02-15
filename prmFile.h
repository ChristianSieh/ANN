#ifndef _PRMFILE_H
#define _PRMFILE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class prmFile
{
	public:
		string weightsFileName;
		int epochs;
		float learningRate;
		float momentum;
		float threshold;
		int layers;
		vector<int> nodesPerLayer;
		string csvFileName;
		int yearsBurned;
		int monthsPDSI;
		int endYear;
		int classes;
		vector<int> range;

		prmFile();
		~prmFile();
		void parsePrm(string prmFileName);
};

#endif
