/******************************************************************************
* File:		prmFile.h
*
* Authors: 	Christian Sieh
*
* Description: 	This file contains a class definition for the class prmFile
*		This class parses the parameter file format specified in the
*		assignment
*
* Date: 	2/21/2016
******************************************************************************/

#ifndef _PRMFILE_H
#define _PRMFILE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

/******************************************************************************
* Class:	prmFile
*
* Description:	Class containing all of the data in the parameter file. This
*		allows all of the nets configuration data to be contained in
*		a single object.
*	
******************************************************************************/
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
