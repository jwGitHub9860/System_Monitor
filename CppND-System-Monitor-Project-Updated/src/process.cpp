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
int Process::Pid() { return 0; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    float cpu_utilization;
    return cpu_utilization = User_col + Nice_col + System_col + Idle_col + Iowait_col + Irq_col + Softirq_col;
}

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User()
{
    string user, line;
    ifstream stream(LinuxParser::kPasswordPath);
    if (stream.is_open())
    {
        getline(stream, line);
        istringstream linestream(line);
        linestream >> user;
        return user;
    }
    return string();
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }