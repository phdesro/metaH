#include "../headers/Job.h"

Job::Job (int nbOp): nbOperations(nbOp) { ops.reserve(nbOp); };

int Job::getNbOperations () { return nbOperations; };

void Job::addOp (Operation opToAdd) { ops.push_back(opToAdd); };

void Job::addMachineToOp(int indexOp, int machineNb, int execTime) {
    ops[indexOp].addNewPair(machineNb, execTime);
}