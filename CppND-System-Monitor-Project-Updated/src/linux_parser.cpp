#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

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
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { return 0.0; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{
  long uptime;  // 1ST LARGE VALUE    { 1st value -> system uptime 2nd value -> system idle time} <---(in Cmake)
  string line;
  ifstream stream(kProcDirectory + kUptimeFilename);  // input file stream from path for operating system kernel version          operating system kernel version - "proc directory + version file name"
  if (stream.is_open())
  {
    getline(stream, line);   // gets line from stream & stores it in "string line"
    istringstream linestream(line);    // creates string stream from "line"
    linestream >> uptime;  // allows to pull tokens off stream     first token - time    78322.97 1119670.94 <---(in Cmake)
  }
  return uptime;  // if opening string or something else fails, return "time" as Blank String Default
}

// TODO: Read and return the number of jiffies for the system   // jiffy - unit of time in <linux/jiffies.h>
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses()
{
  int num_of_run_process;
  string line;
  string key;
  ifstream stream(kProcDirectory + kStatFilename)  // input file stream from path for operating system kernel version          operating system kernel version - "proc directory + version file name"
  if (stream.is_open())
  {
    while (getline(stream, line))   // gets line from stream & stores it in "string line"
    {
      istringstream linestream(line);  // input string stream
      while (linestream >> key >> num_of_run_process)   // allows to pull tokens off stream     first token - num_of_run_process    78322.97 1119670.94 <---(in Cmake)
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
