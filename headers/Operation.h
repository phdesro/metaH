#ifndef OPERATION_H
#define OPERATION_H
#include <vector>
#include <utility>
#include <string>

class Operation {
    int nbMachinesOp;
    int jobNbr;
    int skipNb = 0;
    std::vector< std::pair< int, int> > jobData;
    std::pair< int, int> chosenPair;
    std::pair< int, int> fastestPair;
    std::vector< std::pair< int, int> > pairsToSkip;

  public:
    Operation (int numberMachines, int jobNumber);
    int getNbMachines();
    int getJobNbr();
    std::pair< int, int> getNextFastestPair(std::vector<int> machineCosts, int jobTimeCost);
    void incrementSkipNb();
    void addNewPair(int machineNb, int execTime);
    std::pair< int, int> getFastestPair(std::vector<int> machineCosts, int jobTimeCost);
    Operation* choosePair(int machineNb, int execTime);
    std::pair< int, int> getChosenPair();
    bool getIsSkipped();
    bool isPairSkipped(std::pair< int, int> pairToFind);
};

#endif