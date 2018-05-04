#ifndef DATASET_H
#define DATASET_H
#include "Job.h"
#include <vector>

class DataSet {
    int nbJobs, nbMachines;
    std::vector<Job> jobs;
  public:
    DataSet (int x, int y);
    int getNbJobs();
    int getNbMachines();
    void addJob(Job job);
    void addOperationToJob(int index, Operation op);
    void addMachineToOp(int indexJob, int indexOp, int machineNb, int execTime);
};

#endif