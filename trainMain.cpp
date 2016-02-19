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

	if(argc < 2)
        {
		cout << "USAGE: ANNtrain parameterFile" << endl;
        }
	
	else
	{
		prm.parsePrm(argv[1]);
		cout << "Parameters parsed correctly\n";
		vector<PDSI> csv_data;
		csv_data = parseCSV(prm.csvFileName.c_str());

		neuralNet net;

		net.buildNet(prm);

		net.propogatePerceptrons(prm, csv_data, 15);

		//net.trainNet(prm, csv_data);
	}

	return 0;
}

