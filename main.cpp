#include <iostream>
#include <fstream>
#include <string>
#include "./headers/DataSet.h"
#include "./headers/Job.h"
#include "./headers/Operation.h"
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
	cout << nbJobs << "  " << nbMachines << "\n";
	getline(data, firstLineString);
	DataSet constructedDataSet(stoi(nbJobs, nullptr, 10), stoi(nbMachines, nullptr, 10));
	return constructedDataSet;
}

void generateJobs(istream& cinJobs, DataSet& data) {
	for(int i = 0; i < data.getNbJobs(); i++){
		string nbOp;
		cinJobs >> nbOp;
		int numberOp = stoi(nbOp, nullptr, 10);
		Job tempJob(numberOp);
		data.addJob(tempJob);
		for ( int j = 0; j < numberOp; j++ ) {
			string nbMachineOpStr;
			cinJobs >> nbMachineOpStr;
			int nbMachineOp = stoi(nbMachineOpStr, nullptr, 10);
			Operation tempOp(nbMachineOp);
			data.addOperationToJob(i, tempOp);
			for (int k = 0; k < nbMachineOp; k++) {
				string machineNbStr, execTimeStr;
				cinJobs >> machineNbStr >> execTimeStr;
				data.addMachineToOp(i, j, stoi(machineNbStr, nullptr, 10), stoi(execTimeStr, nullptr, 10));
				cout << machineNbStr << " " << execTimeStr << "\t";
			}
		}
		cout << "\n";
	}
}
