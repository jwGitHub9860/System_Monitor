#ifndef PROCESS_H
#define PROCESS_H

#include <string>

using namespace std;

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);     // constructor ---> DEFINES SPECIFIC "int pid" OF SPECIFIC PROCESS
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int pid_;
  
  int process_ID;

  float cpu_utilization;
  float active_jiffies;
  float idle_jiffies;
  float prev_User;
  float prev_Nice;
  float prev_System;
  float prev_Idle;
  float prev_Iowait;
  float prev_Irq;
  float prev_Softirq;

  string command;

  string mem_usage;

  string user_name;

  long int uptime;
};

#endif