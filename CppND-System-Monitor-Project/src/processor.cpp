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

  float CPU_Percentage = (float)(totald - idled)/(float)totald;
  
  prevuser = user;
  prevnice = nice;
  prevsystem = system;
  previdle = idle;
  previowait = iowait;
  previrq = irq;
  prevsoftirq = softirq;
  prevsteal = steal;
  return CPU_Percentage;
  
}