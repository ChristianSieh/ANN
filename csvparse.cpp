#include "csvparse.h"

vector<PDSI> parseCSV(const char * filename)
{

	ifstream fin;
	fin.open(filename);
	vector<PDSI> csvData;
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
			csvData.push_back(tmp);
		}
	}

	normalizePDSI(csvData);

	return csvData;
}

void normalizePDSI(vector<PDSI> & csvData)
{
	//Find max and min acres burned
	double min_acres = 2147483647;
	double max_acres = -1; //max int
	//Find max and min drought index values
	double min_pdsi = 100;	// These values only have a range from -10 to 10
	double max_pdsi = -100;
	for(unsigned int i = 0; i < csvData.size(); i++)
	{
		if(csvData[i].AcresBurned < min_acres)
			min_acres = csvData[i].AcresBurned;

		else if(csvData[i].AcresBurned > max_acres)
			max_acres = csvData[i].AcresBurned;

		//Now run through the 12 months of pdsi data and see if the years
		//min/max pdsi is a global min/max
		double local_min = 100;
		double local_max = -100;
		for(int j = 0; j < 12; j++)
		{
			if(csvData[i].DroughtIndex[j] < local_min)
				local_min = csvData[i].DroughtIndex[j];

			else if(csvData[i].DroughtIndex[j] > local_max)
				local_max = csvData[i].DroughtIndex[j];
		}
		if(local_min < min_pdsi)
			min_pdsi = local_min;

		if(local_max > max_pdsi)
			max_pdsi = local_max;
		
	}

	// Now we have the min/max from the entire dataset
	for(unsigned int i = 0; i < csvData.size(); i++)
	{
		csvData[i].AcresBurned = (csvData[i].AcresBurned - min_acres) / (max_acres - min_acres);
		
		for(int j = 0; j < 12; j++)
		{
			csvData[i].DroughtIndex[j] = (csvData[i].DroughtIndex[j] - min_pdsi) / (max_pdsi - min_pdsi);
		}
	}
}

void setParam(PDSI & tmp, double n, int index)
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
