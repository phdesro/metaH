#include "../headers/Operation.h"

Operation::Operation (int number): nbMachines(number) { jobData.reserve(number); };

int Operation::getNbMachines () { return nbMachines; };

void Operation::addNewPair(int machineNb, int execTime) {
    std::pair <int,int> tempPair(machineNb, execTime);
    jobData.push_back(tempPair);
};