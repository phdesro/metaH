#include "../headers/DataSet.h"

DataSet::DataSet (int x, int y): nbJobs(x), nbMachines(y) { jobs.reserve(y); };

int DataSet::getNbJobs () { return nbJobs; };

int DataSet::getNbMachines () { return nbMachines; };

void DataSet::addJob (Job job) { jobs.push_back(job); };

void DataSet::addOperationToJob(int index, Operation op) { jobs[index].addOp(op); };

void DataSet::addMachineToOp(int indexJob, int indexOp, int machineNb, int execTime) { 
    jobs[indexJob].addMachineToOp(indexOp, machineNb, execTime);
    };