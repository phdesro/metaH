#include "../headers/DataSet.h"
#include <iostream>

DataSet::DataSet (int x, int y): nbJobs(x), nbMachinesSet(y) { jobs.reserve(y); };

int DataSet::getNbJobs () { return nbJobs; };

int DataSet::getNbMachines () { return nbMachinesSet; };

void DataSet::addJob (Job job) { jobs.push_back(job); };

void DataSet::addOperationToJob(int index, Operation op) { jobs[index].addOp(op); };

void DataSet::addMachineToOp(int indexJob, int indexOp, int machineNb, int execTime) { 
    jobs[indexJob].addMachineToOp(indexOp, machineNb, execTime);
};

int DataSet::calculateTotalNbOp(){
    int nbOpTotal = 0;
    for (int i = 0; i < nbJobs; i++) {
        nbOpTotal += jobs[i].getNbOperations();
    }
    return nbOpTotal;
};

Operation* DataSet::getNextOp(std::vector<int> &machineTimes){
    std::pair< int, int> fastestPair(-1, -1);
    std::pair< int, int> secondFastestPair(-1, -1);
    int jobNumber;
    int isSkipped = false;

    for (int i = 0; i < nbJobs; i++) {
        std::pair< int, int> currentPair = jobs[i].getFastestTimeOp(machineTimes);
        
        if((fastestPair.first==-1 || (fastestPair.second >= currentPair.second)) && currentPair.first != -1) {
            secondFastestPair = fastestPair;
            isSkipped = jobs[i].getIsSkipped();
            fastestPair = currentPair;
            jobNumber = i;
        }
    }

    std::pair< int, int> nextPair(-1, -1);
    if (isSkipped && secondFastestPair.second != -1) {
        bool ongoing = true;
        while(ongoing) {
            nextPair = jobs[jobNumber].getNextFastestPair(machineTimes);
            isSkipped = jobs[jobNumber].getIsSkipped();
            if (nextPair.second >= secondFastestPair.second || nextPair.second == -1) {
                fastestPair = secondFastestPair;
                ongoing = false;
            } else if (nextPair.second < secondFastestPair.second && !isSkipped) {
                fastestPair = nextPair;
                ongoing = false;
            }
        }
    }

    Operation* chosenOperation = chooseNextOp(fastestPair, jobNumber, machineTimes);
    return chosenOperation;
};

void DataSet::resetJobs() {
    for(int i = 0; i< nbJobs; i++) {
        jobs[i].reset();
    }
}

Operation* DataSet::chooseNextOp(std::pair< int, int> chosenPair, int jobNumber, std::vector<int> &machineTimes){
    Operation* chosenOperation = jobs[jobNumber].chooseOp(chosenPair.first, chosenPair.second);
    machineTimes[chosenPair.first] = chosenPair.second;
    return chosenOperation;
};