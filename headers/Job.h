#ifndef JOB_H
#define JOB_H
#include <vector>
#include "Operation.h"

class Job {
    int nbOperations;
    std::vector<Operation> ops;
  public:
    Job (int nbOp);
    int getNbOperations();
    void addOp(Operation opToAdd);
    void addMachineToOp(int indexOp, int machineNb, int execTime);
};

#endif