#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "csvparse.h"
#include "neuralnet.h"
#include "prmFile.h"
#include "weights.h"

using namespace std;

int main(int argc, char * argv[])
{
	prmFile prm;
	double* weightArray;

	if(argc < 2)
        {
		cout << "USAGE: ANNtrain parameterFile" << endl;
        }
	
	else
	{
	prm.parsePrm(argv[1]);		

	vector<PDSI> csv_data;
	csv_data = parseCSV(prm.csvFileName.c_str());

	neuralNet net;

        WeightsSetUp(prm, weightArray);

	net.buildNet(prm);

	net.trainNet(prm, csv_data);
	}

	return 0;
}

