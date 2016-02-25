/******************************************************************************
* File:		crossMain.cpp
*
* Authors: 	Dylan Geyer, Christian Sieh, Jason Anderson
*
* Description: 	This file uses the neural net class to train the net on modified
*		input data and make guesses.
*
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
* Description:	Runs the neural network in cross validation mode. This will
*		remove a year from the training data and run the training
*		and make a guess for the year that was removed. It displays
*		results of the guessing and removes another year and restarts
*		training until all years have been removed and trained.
*
* Parameters:	argc - number of command line arguments
*		argv - array of c style strings containing command line args
*
* Returns:	status integer
******************************************************************************/
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

