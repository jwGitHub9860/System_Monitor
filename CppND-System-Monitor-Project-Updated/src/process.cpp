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

Process::Process(int pid) { pid_ = pid; }     // constructor ---> DEFINES SPECIFIC "int pid" OF SPECIFIC PROCESS

// TODO: Return this process's ID
int Process::Pid() { return process_ID; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    cpu_utilization = prev_User + prev_Nice + prev_System + prev_Idle + prev_Iowait + prev_Irq + prev_Softirq;      // initialize previous values

    vector<string> jiffies = LinuxParser::CpuUtilization();
    active_jiffies = stol(jiffies[LinuxParser::ActiveJiffies()]);   // ACCEPTABLE?
    idle_jiffies = stol(jiffies[LinuxParser::IdleJiffies()]);   // ACCEPTABLE?
    Irq_col = stol(jiffies[LinuxParser::kIRQ_]);
    Softirq_col = stol(jiffies[LinuxParser::kSoftIRQ_]);
    return cpu_utilization;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }