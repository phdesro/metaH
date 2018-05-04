#include "../headers/Operation.h"

Operation::Operation (int number): nbMachines(number) { jobData.reserve(number); };

int Operation::getNbMachines () { return nbMachines; };