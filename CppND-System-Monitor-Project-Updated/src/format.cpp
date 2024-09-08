#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#include "format.h"

using std::string;

using namespace std;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds)    // calculates Uptime into { Hr:Min:Sec }
{
    long hr = seconds / 3600;
    seconds = seconds % 3600;
    long min = seconds / 60;
    long sec = seconds % 60;
    return to_string(hr) + ":" + to_string(min) + ":" + to_string(sec);
    /*vector<int> temp_times{};    // holds sec AFTER calculation     { hr, min, sec }
    vector<int> denominators{ 3600, 60, 1 };    // { hr, min, sec }

    long sec = seconds;     // copy of original system uptime (WILL BE CHANGED TO FIND REAL UPTIME)

    while (sec > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            temp_times[i] = int(floor(sec/temp_times[i]));   // floor() Rounds DOWN to int

            sec -= temp_times[i] * denominators[i];     // subtracts new sec result from original sec
        }
    }
    
    return to_string(temp_times[0]) + ":" + to_string(temp_times[1]) + ":" + to_string(temp_times[2]);      // outputs HH:MM:SS      used '+' because '<<' gives error & only used for 'cout'      converts 'int' to 'string'
    */
}