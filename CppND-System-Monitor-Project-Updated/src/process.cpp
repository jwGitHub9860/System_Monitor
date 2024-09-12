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

Process::Process(int pid) : pid_(pid) {}     // constructor (initializer list) ---> DEFINES SPECIFIC "int pid" OF SPECIFIC PROCESS

// TODO: Return this process's ID
int Process::Pid() { return process_ID; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()
{
    prev_total_jiffies = prev_User + prev_Nice + prev_System + prev_Irq + prev_Softirq;      // initialize previous values
    prev_idle_jiffies = prev_Idle + prev_Iowait;      // initialize previous values
    
    //vector<string> jiffies = LinuxParser::CpuUtilization();
    /*float current_active_jiffies = LinuxParser::ActiveJiffies(pid_);   // ONLY NEED STATES PERTAINING TO CPU ITSELF (NOT GUEST)    Can NOT use "stol(jiffies[LinuxParser::ActiveJiffies()])" or program will NOT Run
    float current_idle_jiffies = LinuxParser::IdleJiffies();   // Can NOT use "stol(jiffies[LinuxParser::IdleJiffies()])" or program will NOT Run*/
    float current_active_jiffies = LinuxParser::kUser_ + LinuxParser::kNice_ + LinuxParser::kSystem_ + LinuxParser::kIRQ_ + LinuxParser::kSoftIRQ_;   // ONLY NEED STATES PERTAINING TO CPU ITSELF (NOT GUEST)    Can NOT use "stol(jiffies[LinuxParser::ActiveJiffies()])" or program will NOT Run
    float current_idle_jiffies = LinuxParser::kIdle_ + LinuxParser::kIOwait_;   // Can NOT use "stol(jiffies[LinuxParser::IdleJiffies()])" or program will NOT Run

    float total_jiffies = current_active_jiffies - prev_total_jiffies;   // apps are ALWAYS opened & closed at anytime ---> MUST USE "current total - previous total"
    float idle_jiffies = current_idle_jiffies - prev_idle_jiffies;      // apps are ALWAYS opened & closed at anytime ---> MUST USE "current idle - previous idle"

    prev_User = LinuxParser::kUser_;    // make Current user, Previous user
    prev_Nice = LinuxParser::kNice_;    // make Current nice, Previous nice
    prev_System = LinuxParser::kSystem_;    // make Current system, Previous system
    prev_Irq = LinuxParser::kIRQ_;    // make Current irq, Previous irq
    prev_Softirq = LinuxParser::kSoftIRQ_;    // make Current softirq, Previous softirq
    prev_Idle = LinuxParser::kIdle_;    // make Current idle, Previous idle
    prev_Iowait = LinuxParser::kIOwait_;    // make Current iowait, Previous iowait

    /*prev_total_jiffies = stol(jiffies[LinuxParser::ActiveJiffies()]);   // ACCEPTABLE?    make Previous total, Current total    ONLY NEED STATES PERTAINING TO CPU ITSELF (NOT GUEST)
    prev_idle_jiffies = stol(jiffies[LinuxParser::IdleJiffies()]);   // ACCEPTABLE?    make Previous idle, Current idle
    */
    /*prev_total_jiffies = current_active_jiffies;   // ACCEPTABLE?    make Previous total, Current total    ONLY NEED STATES PERTAINING TO CPU ITSELF (NOT GUEST)
    prev_idle_jiffies = current_idle_jiffies;   // ACCEPTABLE?    make Previous idle, Current idle*/
    
    return (total_jiffies - idle_jiffies) / total_jiffies;   // CALCULATE PERCENT WITH * 100 OR NOT?                 CPU utilization = Total time - Idle time      CPU utilization will be shown as PERCENTAGE
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram()
{
    /*ram_usage = stoi(LinuxParser::Ram(pid_)) / 1024;    // convert to kB ---> DIVIDE BY 1024
    return to_string(ram_usage);*/
    return LinuxParser::Ram(pid_);
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime() - LinuxParser::UpTime(pid_); }    // Age of process & Uptime of process are NOT the SAME

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return this->ram_usage < a.ram_usage; }