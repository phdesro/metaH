#ifndef DATASET_H
#define DATASET_H
#include "Job.h"
#include <vector>

class DataSet {
    int nbJobs, nbMachinesSet;
    std::vector<Job> jobs;
  public:
    DataSet (int x, int y);
    int getNbJobs();
    int getNbMachines();
    void addJob(Job job);
    void addOperationToJob(int index, Operation op);
    void addMachineToOp(int indexJob, int indexOp, int machineNb, int execTime);
    int calculateTotalNbOp();
    Operation* getNextOp(std::vector<int> &machineTimes);
    Operation* chooseNextOp(std::pair< int, int> chosenPair, int jobNumber, std::vector<int> &machineTimes);
    void resetJobs();
};

#endif