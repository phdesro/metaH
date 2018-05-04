#ifndef OPERATION_H
#define OPERATION_H
#include <vector>
#include <utility>
#include <string>

class Operation {
    int nbMachines;
    std::vector< std::pair< std::string, int> > jobData;
  public:
    Operation (int number);
    int getNbMachines();
};

#endif