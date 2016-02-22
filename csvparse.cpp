/******************************************************************************
* File: 	csvparse.cpp
*
* Authors: 	Dylan Geyer
*
* Description: 	This file contains the class implementation of csvParser. It
*		implements the constructor/destructor, and the functions 
*		parseCSV, normalizePDSI, and setParam.
*
* Date: 	2/21/2016
******************************************************************************/

#include "csvparse.h"

/******************************************************************************
* Function: 	csvParser
*
* Description:	constructor for the class csvParser. Currently empty.
*
* Parameters:	none
*	
* Returns:	none
******************************************************************************/
csvParser::csvParser()
{

}

/******************************************************************************
* Function: 	~csvParser
*
* Description: 	destructor for the class csvParser, currently empty.
*
* Parameters:	none
*
* Returns:	none
******************************************************************************/
csvParser::~csvParser()
{

}

/******************************************************************************
* Function:	parseCSV
*
* Description:	This functions takes a comma separated value filename and
*		parses the data contained inside. It assumes any line that
*		begins with a digit 0-9 is a data line containing a Year,
*		BurnedAcreage, and 12 PDSI values.
*
* Parameters:	filename - cstring containing the csv files name
*
* Returns:	none
******************************************************************************/
void csvParser::parseCSV(const char * filename)
{

	ifstream fin;
	fin.open(filename);

	while(fin)
	{
		char * line = new char[1000];
		fin.getline(line, 1000);
		if(line[0] >= 0x30 && line[0] <= 0x39)
		{
			PDSI tmp;
			char * num;
			int index = 0;
			num = strtok(line, " ,\n");
			while(num != NULL)
			{
				double n = strtod(num, NULL);
				setParam(tmp, n, index);
				num = strtok(NULL, " ,\n");
				index++;
			}
			csv_data.push_back(tmp);
		}
	}

	normalizePDSI();
}

/******************************************************************************
* Function:	normalizePDSI
*
* Description:	This function will look through the csv data and normalize the
*		burned acreage values to 0->1 and all of the PDSI data to 0->1.
*		The maximum burned acreage is saved so that the real burned
*		acreage can be extracted from the 0->1 value since it is just
*		expressed as a percent of the maximum value.
*
* Parameters:	none
*
* Returns:	none
******************************************************************************/
void csvParser::normalizePDSI()
{
	//Find max and min acres burned
	double min_acres = 2147483647;
	double max_acres = -1; //max int
	//Find max and min drought index values
	double min_pdsi = 100;	// These values only have a range from -10 to 10
	double max_pdsi = -100;
	for(unsigned int i = 0; i < csv_data.size(); i++)
	{
		if(csv_data[i].AcresBurned < min_acres)
			min_acres = csv_data[i].AcresBurned;

		else if(csv_data[i].AcresBurned > max_acres)
			max_acres = csv_data[i].AcresBurned;

		//Now run through the 12 months of pdsi data and see if the years
		//min/max pdsi is a global min/max
		double local_min = 100;
		double local_max = -100;
		for(int j = 0; j < 12; j++)
		{
			if(csv_data[i].DroughtIndex[j] < local_min)
				local_min = csv_data[i].DroughtIndex[j];

			else if(csv_data[i].DroughtIndex[j] > local_max)
				local_max = csv_data[i].DroughtIndex[j];
		}
		if(local_min < min_pdsi)
			min_pdsi = local_min;

		if(local_max > max_pdsi)
			max_pdsi = local_max;
		
	}
	//Keep max acres burned for later classification
	maxBurnedAcre = max_acres;

	// Now we have the min/max from the entire dataset
	for(unsigned int i = 0; i < csv_data.size(); i++)
	{
		csv_data[i].AcresBurned = (csv_data[i].AcresBurned - min_acres) / (max_acres - min_acres);
		
		for(int j = 0; j < 12; j++)
		{
			csv_data[i].DroughtIndex[j] = (csv_data[i].DroughtIndex[j] - min_pdsi) / (max_pdsi - min_pdsi);
		}
	}
}

/******************************************************************************
* Function:	setParam
*
* Description:	This function will assign the value in n to a different field
*		int the PDSI object depending on what value is in index.
*
* Parameters:	tmp - PDSI object that will have some field set
*		n - value to be placed in the PDSI object
*		index - number indicating which field of PDSI to be set
*
* Returns:	none
******************************************************************************/
void csvParser::setParam(PDSI & tmp, double n, int index)
{
	switch(index)
	{
		case 0:
			tmp.Year = n;
			break;
		case 1:	
			tmp.AcresBurned = n;
			break;
		default:
			tmp.DroughtIndex[index-2] = n;
	}
}
