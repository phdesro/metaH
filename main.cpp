#include <iostream>
#include <fstream>
#include <string>
#include "./headers/DataSet.h"
using namespace std;

DataSet readFirstLine(istream& cinFirstLine, ifstream& data);
void generateJobs(istream& cinJobs, DataSet& data);

int main(int argc, char** argv) {
	ifstream dataSet(argv[1]);
	if (dataSet.is_open())
	{	
		cin.rdbuf(dataSet.rdbuf());
		DataSet mainDataSet = readFirstLine(cin, dataSet);
		generateJobs(cin, mainDataSet);
	}
	while(1);
	return 0;
}

DataSet readFirstLine(istream& cinFirstLine, ifstream& data) {
	string nbJobs, nbMachines, nextNumber, firstLineString;
	cinFirstLine >> nbJobs >> nbMachines;
	getline(data, firstLineString);
	DataSet constructedDataSet(stoi(nbJobs, nullptr, 10), stoi(nbMachines, nullptr, 10));
	return constructedDataSet;
}

void generateJobs(istream& cinJobs, DataSet& data) {}
