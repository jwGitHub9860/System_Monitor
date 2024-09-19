#include <cmath>
#include <iostream>

#include "processor.h"
#include "linux_parser.h"
#include "process.h"

using namespace std;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
    long total_jiffies = LinuxParser::Jiffies();
    long active_jiffies = LinuxParser::ActiveJiffies();
    
    float total_time = total_jiffies;   // change long to float
    float active_time = active_jiffies;   // change long to float
    
    return (active_time / total_time) * total_time;     // CPU usage percent = (Active_CPU_time / Total_CPU_time) * 100         total_time = 100%
}