#include <cmath>
#include <iostream>

#include "processor.h"
#include "linux_parser.h"

using namespace std;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { return LinuxParser::CpuUtilization(); }