#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

using namespace std;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);  // create file stream from path
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {  // read in line; while loop used due to multiple lines
      std::replace(line.begin(), line.end(), ' ', '_');   // Character Replacement: replace ' ' with '_' (makes lines easier to parse)
      std::replace(line.begin(), line.end(), '=', ' ');   // Character Replacement: replace '=' with ' ' (makes lines easier to parse)
      std::replace(line.begin(), line.end(), '"', ' ');   // Character Replacement: replace '"' with ' ' (makes lines easier to parse)
      std::istringstream linestream(line);  // input string stream
      while (linestream >> key >> value) {  // split line into "key" & "value" (2 tokens)
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);  // input file stream from path for operating system kernel version          operating system kernel version - "proc directory + version file name"
  if (stream.is_open()) {
    std::getline(stream, line);   // gets line from stream & stores it in "string line"
    std::istringstream linestream(line);    // creates string stream from "line"
    linestream >> os >> version >> kernel;  // allows to pull tokens off stream     first token - os (operating system name --> Linux)     second token - version     third token - kernel    Linux version 5.15.154+ <---(in Cmake)
  }
  return kernel;  // if opening string or something else fails, return "kernel" as Blank String Default
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), ::isdigit)) {   // Changed "isdigit" to "::isdigit" to make code work in workspace
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization()
{
  float total_memory, free_memory;
  string key, line;
  float value;
  ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open())
  {
    while (getline(stream, line))  // read in line; while loop used due to multiple lines
    {
      istringstream linestream(line);    // creates string stream from "line"
      linestream >> key >> value;  // allows to pull tokens off stream     1st token - key     2nd token - value
      if (key == "MemTotal:")  // check if "line" holds cpu info (line = cpu / cpu...#)
      {
        total_memory = value;
      }
      else if (key == "MemFree:")
      {
        free_memory = value;
      }
    }
  }
  return (total_memory - free_memory) / (total_memory * 100);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{
  long uptime;  // 1ST LARGE VALUE & 2nd large value    { 1st value -> system uptime 2nd value -> system idle time} <---(in Cmake)
  string line;
  ifstream stream(kProcDirectory + kUptimeFilename);  // input file stream from path for operating system kernel version          operating system kernel version - "proc directory + version file name"
  if (stream.is_open())
  {
    getline(stream, line);   // gets line from stream & stores it in "string line"
    istringstream linestream(line);    // creates string stream from "line"
    linestream >> uptime;  // allows to pull tokens off stream     1st token - uptime     2nd token - idle_time    78322.97 1119670.94 <---(in Cmake)   MUST INCLUDE BOTH UPTIME & IDLE TIME or error will be returned
  }
  return uptime;  // if opening string or something else fails, return "uptime" as Blank String Default     MUST CHANGE "uptime" from 'string' to 'long' LAST or error will be returned
}

// TODO: Read and return the number of jiffies for the system   // jiffy - unit of time in <linux/jiffies.h>
long LinuxParser::Jiffies()   // JIFFIES ARE THE LARGE NUMBERS
{
  long num_of_jiff;  // 2ND LARGE VALUE    { 1st value -> cpu, 2nd value -> user int, 3rd value -> nice int, 4th value -> system int, 5th value -> idle int, 6th token - irq int, 7th token - softirq int} <---(in Cmake)
  string key, line;
  ifstream stream(kProcDirectory + kStatFilename)  // input file stream from path for operating system kernel version          operating system kernel version - "proc directory + stat file name"

  int user, nice, system, idle, iowait, irq, softirq;
  string find_cpu = line.substr(0, 3);    // finds cpu information

  if (stream.is_open())
  {
    while (getline(stream, line))  // read in line; while loop used due to multiple lines
    {
      istringstream linestream(line);    // creates string stream from "line"
      linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq;  // allows to pull tokens off stream     first token - user     second token - nice     third token - system     fouth token - idle     fifth token - iowait     sixth token - irq     seventh token - softirq
      if (find_cpu == "cpu")  // check if "line" holds cpu info (line = cpu / cpu...#)
      {
        return user;
      }
    }
  }
  return user;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies()
{
  long active_jiffies;  // 3RD LARGE VALUE <---(is it really?)    { 1st value -> cpu, 2nd value -> user int, 3rd value -> nice int, 4th value -> system int, 5th value -> idle int, 6th token - irq int, 7th token - softirq int} <---(in Cmake)
  string line;
  ifstream stream(kProcDirectory + kStatFilename)  // input file stream from path for operating system kernel version          operating system kernel version - "proc directory + stat file name"

  int user, nice, system, idle, iowait, irq, softirq;
  string find_cpu = line.substr(0, 3);    // finds cpu information

  if (stream.is_open())
  {
    while (getline(stream, line))  // read in line; while loop used due to multiple lines
    {
      istringstream linestream(line);    // creates string stream from "line"
      linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq;  // allows to pull tokens off stream     first token - user     second token - nice     third token - system     fouth token - idle     fifth token - iowait     sixth token - irq     seventh token - softirq
      if (find_cpu == "cpu")  // check if "line" holds cpu info (line = cpu / cpu...#)
      {
        return nice;
      }
    }
  }
  return nice;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies()
{
  long active_jiffies;  // 3RD LARGE VALUE <---(is it really?)    { 1st value -> cpu, 2nd value -> user int, 3rd value -> nice int, 4th value -> system int, 5th value -> idle int, 6th token - irq int, 7th token - softirq int} <---(in Cmake)
  string line;
  ifstream stream(kProcDirectory + kStatFilename)  // input file stream from path for operating system kernel version          operating system kernel version - "proc directory + stat file name"

  int user, nice, system, idle, iowait, irq, softirq;
  string find_cpu = line.substr(0, 3);    // finds cpu information

  if (stream.is_open())
  {
    while (getline(stream, line))  // read in line; while loop used due to multiple lines
    {
      istringstream linestream(line);    // creates string stream from "line"
      linestream >> user >> nice >> system >> idle >> iowait >> irq >> softirq;  // allows to pull tokens off stream     first token - user     second token - nice     third token - system     fouth token - idle     fifth token - iowait     sixth token - irq     seventh token - softirq
      if (find_cpu == "cpu")  // check if "line" holds cpu info (line = cpu / cpu...#)
      {
        return idle;
      }
    }
  }
  return idle;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses()
{
  int total_processes;
  string line;
  string key;
  ifstream stream(kProcDirectory + kStatFilename);  // input file stream from path for operating system kernel version          operating system kernel version - "proc directory + stat file name"
  if (stream.is_open())
  {
    while (getline(stream, line))   // gets line from stream & stores it in "string line"
    {
      istringstream linestream;  // input string stream
      while (linestream >> key >> total_processes)   // gets line from stream & stores it in "string line"     first token - processes    second token - " # "    78322.97 1119670.94 <---(in Cmake)
      {
        if (key == "processes")   // checks if line contains total number of processes
        {
          return total_processes;
        }
      }
    }
  }
  return total_processes;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  int num_of_run_process;
  string line;
  string key;
  ifstream stream(kProcDirectory + kStatFilename)  // input file stream from path for operating system kernel version          operating system kernel version - "proc directory + stat file name"
  if (stream.is_open())
  {
    while (getline(stream, line))   // gets line from stream & stores it in "string line"
    {
      istringstream linestream(line);  // input string stream
      while (linestream >> key >> num_of_run_process)   // allows to pull tokens off stream     first token - procs_running    second token - " # "    78322.97 1119670.94 <---(in Cmake)
      {
        if (key == "procs_running")   // checks if line contains number of processes running
        {
          return num_of_run_process;
        }
      }
    }
  }
  return num_of_run_process;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
