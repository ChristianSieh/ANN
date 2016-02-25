/******************************************************************************
* File:		trainMain.cpp
*
* Authors: 	Dylan Geyer, Christian Sieh, Jason Anderson
*
* Description: 	This file uses the neural net class to back propogate and train
*		the weights file.
*
* Date: 	2/21/2016
******************************************************************************/
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

/******************************************************************************
* Function:	main
*
* Description:	Runs the neural network in training mode wich will update the
*		values in the weights file.
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
		cout << "USAGE: ANNtrain parameterFile" << endl;
        }
	
	else
	{
		prm.parsePrm(argv[1]);
		cout << "Parameters parsed correctly\n";
		vector<PDSI> csv_data;
		csv.parseCSV(prm.csvFileName.c_str());

		neuralNet net;

		net.buildNet(prm);
		
		net.trainNet(prm, csv);

		net.wts.WriteWeightsToFile(prm);

		//net.previousWts.PrintWeights();
		//net.wts.PrintWeights();
	}

	return 0;
}

