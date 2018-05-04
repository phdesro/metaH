#include "../headers/DataSet.h"

DataSet::DataSet (int x, int y): nbJobs(x), nbMachines(y) { jobs.reserve(y); };

int DataSet::getNbJobs () { return nbJobs; };

int DataSet::getNbMachines () { return nbMachines; };