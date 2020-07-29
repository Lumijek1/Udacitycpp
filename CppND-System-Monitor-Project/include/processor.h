#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  long int prevuser = 0;
  long int prevnice = 0;
  long int prevsystem = 0;
  long int previdle = 0;
  long int previowait = 0;
  long int previrq = 0;
  long int prevsoftirq = 0;
  long int prevsteal = 0;

};

#endif