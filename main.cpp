#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "csvparse.h"

using namespace std;

int main(int argc, char * argv[])
{
	vector<PDSI> csv_data;
	csv_data = parseCSV("PDSI_BH_1978-2015.csv");

	return 0;
}

