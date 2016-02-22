/******************************************************************************
* File: 	csvparse.h
*
* Authors: 	Dylan Geyer
*
* Description: 	Contains class and struct definitions for the csvParse class.
*
* Date: 	2/21/2016
******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

#ifndef CVPARSE_H
#define CVPARSE_H

/******************************************************************************
* Struct:	PDSI
*
* Description:	This struct simply packages all of the data types found in the
*		comma separated value file used in csvParser. Each years data
*		is put together to create on PDSI object.
*	
******************************************************************************/
struct PDSI
{
	int Year;
	float AcresBurned;
	float DroughtIndex[12];
};

/******************************************************************************
* Class:	csvParser
*
* Description:	This class will extract the data stored in a comma separated
*		value file, specificaly one containing PDSI data.
*	
******************************************************************************/
class csvParser
{
	public:
		double maxBurnedAcre;
		vector<PDSI> csv_data;
		
		csvParser();
		~csvParser();
		void parseCSV(const char * filename);
		void normalizePDSI();

	private:
		void setParam(PDSI & tmp, double n, int index);
};


#endif
