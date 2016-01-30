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


	return csvData;
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
