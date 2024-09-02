#include "processor.h"
#include "linux_parser.h"
#include "process.h"

using namespace std;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    cpu_percent = LinuxParser::CpuUtilization();
    active_time = stof(cpu_percent[0]) + stof(cpu_percent[1]) + stof(cpu_percent[2]);
    idle_time = stof(cpu_percent[3]) + stof(cpu_percent[4]);
    return active_time + idle_time;
}