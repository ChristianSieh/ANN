#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "prmFile.h"
#include "csvparse.h"
#include "neuralnet.h"

using namespace std;

int main(int argc, char * argv[])
{
	prmFile prm;

	csvParser csv;


	if(argc < 2)
	{
		cout << "USAGE: CrossValidate parameterFile" << endl; 
	}

	else
	{
		prm.parsePrm(argv[1]);		
	
		vector<PDSI> csv_data;

		csv.parseCSV(prm.csvFileName.c_str());
	
		neuralNet net;

		net.buildNet(prm);

		net.crossValidate(prm, csv);
	}
	
	return 0;
}

