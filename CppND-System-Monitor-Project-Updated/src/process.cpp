#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

using namespace std;

// TODO: Return this process's ID
int Process::Pid() { return process_ID; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    float cpu_utilization;
    return cpu_utilization = User_col + Nice_col + System_col + Idle_col + Iowait_col + Irq_col + Softirq_col;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return mem_usage; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_name; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }