#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
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
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
    
  }
  return kernel;
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
float LinuxParser::MemoryUtilization() { 
  string line, key, value;
  float mFree, mTotal;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if(filestream.is_open()){
    while (std::getline(filestream, line)) {
      std::remove(line.begin(), line.end(), ' ');   
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if(key == "MemTotal"){
          mTotal = std::stof(value);
        }
        if(key == "MemFree"){
          mFree = std::stof(value);
        }
      }
    }
  }
  return ((mTotal-mFree)/mTotal);
}

// TODO: Read and return the system uptime
long int LinuxParser::UpTime() { 
  string line, upTime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  long TotalUpTime = 0;
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> upTime;
    TotalUpTime = std::stol(upTime);
  }
  return TotalUpTime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpu = {};
  string line, key, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  while(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while(linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice){
      if(key == "cpu"){
        cpu.push_back(user);
        cpu.push_back(nice);
        cpu.push_back(system);
        cpu.push_back(idle);
        cpu.push_back(iowait);
        cpu.push_back(irq);
        cpu.push_back(softirq);
        cpu.push_back(steal);
        cpu.push_back(guest);
        cpu.push_back(guest_nice);
        return cpu;
      }
    }
  }
  return cpu;

}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line, key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  int TotalProcesses = 0;
  if(filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "processes"){
          TotalProcesses = std::stoi(value);
          return TotalProcesses;
        }
      }
    }
  }
  return TotalProcesses;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line, key, value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  int running = 0;
  if(filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> value){
        if(key == "procs_running"){
          running = std::stoi(value);
          return running;
        }
      }
    }
  }
  return running;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line, key;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);  
    linestream >> key;
    return key;
  }
  return "";
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);  
      linestream >> key >> value;
      if(key == "VmSize:"){
        int mb = std::stoi(value) / 1024;
        return std::to_string(mb);
      }
    }
  }
  return "";
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  string line, key, value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::istringstream linestream(line);  
      linestream >> key >> value;
      if(key == "Uid:"){
        return value;
      }
    }
  }
  return "";
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line, user, x, id;
  string Uid = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open()){
    while(std::getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> x >> id;
      if(id == Uid){
        return user;
      }
    }
  }
  return "";
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  string line, value;
  long upTime;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    for(int i = 0; i < 22; i++){
      linestream >> value;
    }
    upTime = std::stol(value) / sysconf(_SC_CLK_TCK);
    return UpTime() - upTime;
  }
  return 0;
}
float LinuxParser::CpuUtilization(int pid){
  string line, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q;
  vector<int> times;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j >> k >> l >> m >> n >> o >> p >> q;
    times.push_back(std::stoi(n));
    times.push_back(std::stoi(o));
    times.push_back(std::stoi(p));
    times.push_back(std::stoi(q));
  }
  int total_time = times[0] + times[1] + times[2] + times[3];
  int seconds = LinuxParser::UpTime() - (LinuxParser::UpTime(pid) / sysconf(_SC_CLK_TCK));
  float cpu_usage = (((float)total_time/(float)sysconf(_SC_CLK_TCK))/(float)seconds);
  return cpu_usage;
}