#ifndef JOB_H
#define JOB_H
#include <vector>
#include "Operation.h"

class Job {
    int nbOperations;
    int jobNb;
    int currentOperationIndex;
    int timeElapsed;
    std::vector<Operation> ops;

  public:
    Job (int nbOp, int nJob);
    int getNbOperations();
    bool getIsSkipped();
    void addOp(Operation opToAdd);
    void addMachineToOp(int indexOp, int machineNb, int execTime);
    std::pair< int, int> getFastestTimeOp(std::vector<int> &machineCosts);
    std::pair< int, int> getNextFastestPair(std::vector<int> &machineCosts);
    Operation* chooseOp(int machineNb, int execTime);
    void reset();
};

#endif