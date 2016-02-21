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
	prm.parsePrm(argv[1]);		
	csv.parseCSV(prm.csvFileName.c_str());
	
	neuralNet net;

	net.buildNet(prm);

	net.testNet(prm, csv);
	
	return 0;
}

