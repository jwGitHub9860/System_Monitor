#include <cmath>
#include <iostream>

#include "processor.h"
#include "linux_parser.h"
#include "process.h"

using namespace std;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    vector<string> cpu_info = LinuxParser::CpuUtilization();
    float active_time = stof(cpu_info[0]) + stof(cpu_info[1]) + stof(cpu_info[2]);    // active_time = user + nice + system
    float total_time = 0;
    for (auto i : cpu_info)    // iterates through ALL Cpu columns
    {
        total_time += stof(i);
    }
    
    return (active_time / total_time) * 100;     // CPU usage percent = (Active_CPU_time / Total_CPU_time) * 100
}