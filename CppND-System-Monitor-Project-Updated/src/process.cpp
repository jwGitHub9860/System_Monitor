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
    prev_total_jiffies = prev_User + prev_Nice + prev_System + prev_Irq + prev_Softirq;      // initialize previous values
    prev_idle_jiffies = prev_Idle + prev_Iowait;      // initialize previous values
    
    vector<string> jiffies = LinuxParser::CpuUtilization();
    float current_total_jiffies = stol(jiffies[LinuxParser::Jiffies()]);   // ACCEPTABLE?    ONLY NEED STATES PERTAINING TO CPU ITSELF (NOT GUEST)
    float current_idle_jiffies = stol(jiffies[LinuxParser::IdleJiffies()]);   // ACCEPTABLE?

    float total_jiffies = current_total_jiffies - prev_total_jiffies;   // apps are ALWAYS opened & closed at anytime ---> MUST USE "current total - previous total"
    float idle_jiffies = current_idle_jiffies - prev_idle_jiffies;      // apps are ALWAYS opened & closed at anytime ---> MUST USE "current idle - previous idle"

    prev_total_jiffies = stol(jiffies[LinuxParser::Jiffies()]);   // ACCEPTABLE?    make Previous total, Current total    ONLY NEED STATES PERTAINING TO CPU ITSELF (NOT GUEST)
    prev_idle_jiffies = stol(jiffies[LinuxParser::IdleJiffies()]);   // ACCEPTABLE?    make Previous idle, Current idle
    
    return (total_jiffies - idle_jiffies) / total_jiffies;   // CALCULATE PERCENT WITH * 100 OR NOT?                 CPU utilization = Total time - Idle time      CPU utilization will be shown as PERCENTAGE
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime() - LinuxParser::UpTime(pid_); }    // Age of process & Uptime of process are NOT the SAME

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }