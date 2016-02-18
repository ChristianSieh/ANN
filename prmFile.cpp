#include "prmFile.h"

using namespace std;

prmFile::prmFile(void)
{
};

prmFile::~prmFile(void)
{
};

vector<string> split(const string &s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> elems;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void prmFile::parsePrm(string prmFileName)
{
	vector<string> parameters;
	vector<string> splitString;
	string temp;
	string toss;
	string::size_type sz;
	int intConvert;
	ifstream prmFile;

	prmFile.open(prmFileName.c_str());
	
	if(!prmFile)
		cout << "PRM file did not open" << endl;

	while(prmFile && parameters.size() < 14)
	{
		if(prmFile.peek() == '#' || prmFile.peek() == '\n')
		{
			getline(prmFile, toss);
		}
		else
		{
			getline(prmFile, temp);
			parameters.push_back(temp);
		}
	}

	splitString = split(parameters[0], ' ');
	weightsFileName = splitString[0];
	splitString = split(parameters[1], ' ');
	epochs = stoi(splitString[0]);
	splitString = split(parameters[2], ' ');
	learningRate = stof(splitString[0],&sz);
	splitString = split(parameters[3], ' ');
	momentum = stof(splitString[0],&sz);
	splitString = split(parameters[4], ' ');
	threshold = stof(splitString[0],&sz);
	splitString = split(parameters[5], ' ');
	layers = stoi(splitString[0],nullptr,0)+1;
	splitString = split(parameters[6], ' ');
	for(int i = 0; i < layers; i++)
	{
		intConvert = stoi(splitString[i]);
		nodesPerLayer.push_back(intConvert);
	}
	
	splitString = split(parameters[7], ' ');
	csvFileName = splitString[0];
	splitString = split(parameters[8], ' ');
	yearsBurned = stoi(splitString[0]);
	splitString = split(parameters[9], ' ');
	monthsPDSI = stoi(splitString[0]);
	splitString = split(parameters[10], ' ');
	endYear = stoi(splitString[0]);
	splitString = split(parameters[11], ' ');
	classes = stoi(splitString[0]);
	for(int i = 0; i < classes - 1; i++)
	{	
		range.push_back(stoi(parameters[12+i]));	
	}
}
