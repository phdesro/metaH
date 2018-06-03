#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "./headers/DataSet.h"
#include "./headers/Job.h"
#include "./headers/Operation.h"
using namespace std;

DataSet readFirstLine(istream& cinFirstLine, ifstream& data);
void generateJobs(istream& cinJobs, DataSet& data);
int generateSolution(DataSet& data, vector<Operation*> &operationOrder);

const int MAX_TRIES = 500;
const int RANDOM_SEED = 79;

int main(int argc, char** argv) {
	ifstream dataSet(argv[1]);
	srand(RANDOM_SEED);
	int bestSolutionTime;
	vector<Operation*> currentOperationOrder;
	DataSet mainDataSet(0,0);
	if (dataSet.is_open())
	{	
		cin.rdbuf(dataSet.rdbuf());
		mainDataSet = readFirstLine(cin, dataSet);
		generateJobs(cin, mainDataSet);
		dataSet.close();
		bestSolutionTime = generateSolution(mainDataSet, currentOperationOrder);
	}

	ofstream solutionFile;
	solutionFile.open ("solutionFile.txt");
	solutionFile << "Solution initiale: " << bestSolutionTime << "\n";
	for (int i = 0; i < (int)currentOperationOrder.size(); i++) {
		std::pair< int, int> chosenPair = currentOperationOrder[i]->getChosenPair();
		solutionFile << "Op nb " << i + 1 << "   machine: " <<
			chosenPair.first + 1 << "   time: " << chosenPair.second << "\n";
	}
	
	int tries=1;
	vector<Operation*> opsToSkip;
	vector<int> skipNbs;
	while(tries <= MAX_TRIES) {
		int skipNb = (rand() % (currentOperationOrder.size()));
		opsToSkip.push_back(currentOperationOrder[skipNb]);
		skipNbs.push_back(skipNb);
		

		vector<Operation*> newOperationOrder;

		solutionFile << "\n\n ------------------------------------------------------------- \n\n\n";

		solutionFile << "Ops skipped: ";

		for( int i = 0; i < opsToSkip.size(); i++ ) {
			opsToSkip[i]->incrementSkipNb();
			solutionFile << "  " << skipNbs[i]+1 << "  ";
		}

		solutionFile << "\n";
		
		mainDataSet.resetJobs();
		int newSolutionTime = generateSolution(mainDataSet, newOperationOrder);
		solutionFile << "Resultat : " << newSolutionTime << "\n";
		if (newSolutionTime < bestSolutionTime) {
			bestSolutionTime = newSolutionTime;
			currentOperationOrder = newOperationOrder;
		} else {
			opsToSkip.pop_back();
			skipNbs.pop_back();
		}
		tries++;
	}
	solutionFile << "\n\n ------------------------------------------------------------- \n\n\n";
	solutionFile << "Solution Finale: " << bestSolutionTime << "\n";
	solutionFile << "Ops skipped: ";
	for ( int i = 0; i < skipNbs.size(); i++ ) {
			solutionFile << "  " << skipNbs[i]+1 << "  ";
		}
	solutionFile << "\n\n";

	ofstream graphFile;
  	graphFile.open ("graphFile.txt");
	ofstream vectorFile;
  	vectorFile.open ("vectorFile.txt");
	string machineOrder = "MA = (";
	string jobOrder = "OS = (";

	for (int i = 0; i < (int)currentOperationOrder.size(); i++) {
		int jobNb = currentOperationOrder[i]->getJobNbr() + 1;
		jobOrder += to_string(jobNb) + ", ";
		std::pair< int, int> chosenPair = currentOperationOrder[i]->getChosenPair();
		int machineNb = chosenPair.first + 1;
		machineOrder += to_string(machineNb) + ", ";
		graphFile << i + 1 << " " << machineNb << "\n";
		solutionFile << "Op nb " << i + 1 << "   machine: " <<
			machineNb << "   JobNb: " << jobNb << 
			"   time: " << chosenPair.second << "\n";
	}

	machineOrder = machineOrder.substr(0, machineOrder.length()-2) + ")";
	jobOrder = jobOrder.substr(0, jobOrder.length()-2) + ")";
	vectorFile << machineOrder << "\n";
	vectorFile << jobOrder;

  	graphFile.close();
	solutionFile.close();
	vectorFile.close();
	return 0;
}

DataSet readFirstLine(istream& cinFirstLine, ifstream& data) {
	string nbJobs, nbMachines, nextNumber, firstLineString;
	cinFirstLine >> nbJobs >> nbMachines;
	getline(data, firstLineString);
	DataSet constructedDataSet(stoi(nbJobs, nullptr, 10), stoi(nbMachines, nullptr, 10));
	return constructedDataSet;
}

int generateSolution(DataSet& data, vector<Operation*> &operationOrder) {
	int nbOpToOrder = data.calculateTotalNbOp();
	vector<int> machineTime;

	for (int i=0; i < data.getNbMachines(); i++) {
		machineTime.push_back(0);
	}
	
	while ((int)operationOrder.size() != nbOpToOrder) {
		operationOrder.push_back(data.getNextOp(machineTime));
		std::pair< int, int> chosenPair = operationOrder.back()->getChosenPair();
	}
	int slowestMachineTime = 0;
	int slowestMachineNumber = -1;
	for(int i =0; i < data.getNbMachines(); i++) {
		if(machineTime[i] > slowestMachineTime){
			slowestMachineTime = machineTime[i];
			slowestMachineNumber = i;
		}
	}

	return slowestMachineTime;
}

void generateJobs(istream& cinJobs, DataSet& data) {
	for(int i = 0; i < data.getNbJobs(); i++){
		string nbOp;
		cinJobs >> nbOp;
		int numberOp = stoi(nbOp, nullptr, 10);
		Job tempJob(numberOp, i);
		data.addJob(tempJob);
		for ( int j = 0; j < numberOp; j++ ) {
			string nbMachineOpStr;
			cinJobs >> nbMachineOpStr;
			int nbMachineOp = stoi(nbMachineOpStr, nullptr, 10);
			Operation tempOp(nbMachineOp, i);
			data.addOperationToJob(i, tempOp);
			for (int k = 0; k < nbMachineOp; k++) {
				string machineNbStr, execTimeStr;
				cinJobs >> machineNbStr >> execTimeStr;
				data.addMachineToOp(i, j, stoi(machineNbStr, nullptr, 10)-1, stoi(execTimeStr, nullptr, 10));
			}
		}
	}
}
