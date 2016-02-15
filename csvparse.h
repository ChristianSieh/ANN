#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

#ifndef CVPARSE_H
#define CVPARSE_H

enum MONTHS
{
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

struct PDSI
{
	int Year;
	float AcresBurned;
	float DroughtIndex[12];
};

vector<PDSI> parseCSV(const char * filename);
void setParam(PDSI & tmp, double n, int index);
void normalizePDSI(vector<PDSI> & csvData);

#endif
