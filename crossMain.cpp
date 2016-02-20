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

	prm.parsePrm(argv[1]);		

	neuralNet net;

	net.buildNet(prm);

	net.crossValidate();
	
	return 0;
}

