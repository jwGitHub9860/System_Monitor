#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

#include "process.h"
#include "system.h"

using namespace std;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  vector<Process> system_Pids;
  string user;
  float cpu_percent;
  string ram;
  long int time;
  string command;
};

#endif