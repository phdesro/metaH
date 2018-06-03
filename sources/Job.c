#include "../headers/Job.h"

Job::Job (int nbOp, int nJob): nbOperations(nbOp), jobNb(nJob)  { 
    ops.reserve(nbOp); 
    timeElapsed = 0;
    currentOperationIndex = 0;
    };

int Job::getNbOperations () { return nbOperations; };

void Job::addOp (Operation opToAdd) { ops.push_back(opToAdd); };

void Job::addMachineToOp(int indexOp, int machineNb, int execTime) {
    ops[indexOp].addNewPair(machineNb, execTime);
}

std::pair< int, int> Job::getFastestTimeOp(std::vector<int> &machineCosts){
    std::pair< int, int> fastestOp(-1,-1);
    if  (currentOperationIndex < nbOperations){
        fastestOp = ops[currentOperationIndex].getFastestPair(machineCosts, timeElapsed);
    }
    return fastestOp;
}

 void Job::reset() {
     currentOperationIndex = 0;
     timeElapsed = 0;
 }

std::pair< int, int> Job::getNextFastestPair(std::vector<int> &machineCosts){
    std::pair< int, int> fastestOp(-1,-1);
    if  (currentOperationIndex < nbOperations){
        fastestOp = ops[currentOperationIndex].getNextFastestPair(machineCosts, timeElapsed);
    }
    return fastestOp;
}

bool Job::getIsSkipped() {
    ops[currentOperationIndex].getIsSkipped();
}

Operation* Job::chooseOp(int machineNb, int execTime) {
    timeElapsed = execTime;
    Operation* opToReturn = new Operation(0, 0);
    if(currentOperationIndex < nbOperations) {
        opToReturn = ops[currentOperationIndex].choosePair(machineNb, execTime);
        currentOperationIndex++;
    }
    return opToReturn;
};