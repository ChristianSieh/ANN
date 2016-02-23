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
	if(argc < 2)
	{
		cout << "USAGE: ANNtest parameterFile" << endl;
	}
	else
	{
		prmFile prm;
		csvParser csv;
		prm.parsePrm(argv[1]);		
		csv.parseCSV(prm.csvFileName.c_str());
		
		neuralNet net;

		net.buildNet(prm);

		net.testNet(prm, csv);
	}
	
	return 0;
}

