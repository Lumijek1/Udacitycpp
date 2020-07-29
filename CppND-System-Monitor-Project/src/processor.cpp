#include "processor.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <string>

#include "linux_parser.h"

using std::string;
using std::vector;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  vector<string> prev = LinuxParser::CpuUtilization();
  
  long int prevuser = std::stol(prev[0]);
  long int prevnice = std::stol(prev[1]);
  long int prevsystem = std::stol(prev[2]);
  long int previdle = std::stol(prev[3]);
  long int previowait = std::stol(prev[4]);
  long int previrq = std::stol(prev[5]);
  long int prevsoftirq = std::stol(prev[6]);
  long int prevsteal = std::stol(prev[7]);
  
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  
  vector<string> current = LinuxParser::CpuUtilization();
  
  long int user = std::stol(current[0]);
  long int nice = std::stol(current[1]);
  long int system = std::stol(current[2]);
  long int idle = std::stol(current[3]);
  long int iowait = std::stol(current[4]);
  long int irq = std::stol(current[5]);
  long int softirq = std::stol(current[6]);
  long int steal = std::stol(current[7]);
  
  long int PrevIdle = previdle + previowait;
  long int Idle = idle + iowait;
  long int PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
  long int NonIdle = user + nice + system + irq + softirq + steal;
  long int PrevTotal = PrevIdle + PrevNonIdle;
  long int Total = Idle + NonIdle;
  long int totald = Total - PrevTotal;
  long int idled = Idle - PrevIdle;

  long int CPU_Percentage = (totald - idled)/totald;
  return CPU_Percentage;
  
}