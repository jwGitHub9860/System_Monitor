#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int process_ID;
  
  float User_col;
  float Nice_col;
  float System_col;
  float Idle_col;
  float Iowait_col;
  float Irq_col;
  float Softirq_col;

  string command;

  string mem_usage;
  string mem_total;
  string mem_free;

  string user_name;

  long int uptime;
};

#endif