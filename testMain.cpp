/******************************************************************************
* File:		testMain.cpp
*
* Authors: 	Dylan Geyer, Christian Sieh, Jason Anderson
*
* Description: 	This file uses the neural net class to make guesses.
* Date: 	2/21/2016
******************************************************************************/
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

/******************************************************************************
* Function:	main
*
* Description:	Runs the neural network in testing mode which simply runs
*		input data through the net and looks at the output.
*
* Parameters:	argc - number of command line arguments
*		argv - array of c style strings containing command line args
*
* Returns:	status integer
******************************************************************************/
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

