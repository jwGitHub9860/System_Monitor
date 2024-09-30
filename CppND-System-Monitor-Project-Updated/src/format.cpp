#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "format.h"

using std::string;

using namespace std;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)    // calculates Uptime into { Hr:Min:Sec }
{
    int hours = seconds / 3600;
    seconds %= 3600;
    int minutes = seconds / 60;
    seconds %= 60;
    std::ostringstream stream;
    stream << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;
    return stream.str();
}