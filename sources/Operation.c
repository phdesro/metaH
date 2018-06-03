#include "../headers/Operation.h"
#include <iostream>
#include <algorithm>

Operation::Operation (int number, int jobNumber): nbMachinesOp(number), jobNbr(jobNumber) { 
    jobData.reserve(number);
};

int Operation::getNbMachines () { return nbMachinesOp; };

int Operation::getJobNbr () { return jobNbr; };

bool Operation::getIsSkipped() {
    return (skipNb > 0);
}

std::pair< int, int> Operation::getNextFastestPair (std::vector<int> machineCosts, int jobTimeCost) { 
    skipNb--;
    pairsToSkip.push_back(fastestPair);
    std::pair< int, int> secondFastestPair(-1, -1);
    for(int i = 0; i < nbMachinesOp; i++) {
        int currentPairCost = jobData[i].second + std::max(jobTimeCost, machineCosts[jobData[i].first]);
        std::pair< int, int> currentPair(jobData[i].first, currentPairCost);
        if((secondFastestPair.first==-1 || (secondFastestPair.second > currentPairCost)) && 
            !isPairSkipped(currentPair)) {
            secondFastestPair = currentPair;
        }
    }
    return secondFastestPair; 
 };

 bool Operation::isPairSkipped(std::pair< int, int> pairToFind) {
     bool isSkipped = false;
     int i = 0;
     while (!isSkipped && i < pairsToSkip.size()) {
         if (pairsToSkip[i].first == pairToFind.first && pairsToSkip[i].second == pairToFind.second) {
             isSkipped = true;
         }
         i++;
     }
     return isSkipped;
 }

void Operation::addNewPair(int machineNb, int execTime) {
    std::pair <int,int> tempPair(machineNb, execTime);
    jobData.push_back(tempPair);
};

std::pair< int, int> Operation::getFastestPair (std::vector<int> machineCosts, int jobTimeCost) {
    fastestPair.first = -1;
    fastestPair.second = -1;
    for(int i = 0; i < nbMachinesOp; i++) {
        int currentPairCost = jobData[i].second + std::max(jobTimeCost, machineCosts[jobData[i].first]);
        std::pair< int, int> currentPair(jobData[i].first, currentPairCost);
        if(fastestPair.first==-1 || (fastestPair.second > currentPairCost)) {
            fastestPair = currentPair;
        }
    }
    return fastestPair; 
};

Operation* Operation::choosePair(int machineNb, int execTime) {
    chosenPair.first = machineNb;
    chosenPair.second = execTime;
    skipNb = 0;
    return this;
};

std::pair< int, int> Operation::getChosenPair(){
    return chosenPair;
}

void Operation::incrementSkipNb() {
    skipNb++;
}