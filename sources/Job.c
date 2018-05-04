#include "../headers/Job.h"

Job::Job (int nbOp): nbOperations(nbOp) { ops.reserve(nbOp); };

int Job::getNbOperations () { return nbOperations; };