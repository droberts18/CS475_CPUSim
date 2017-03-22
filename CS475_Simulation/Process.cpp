#include "Process.h"

void Process::setCompletionTime(int completionTime){ this->completionTime = completionTime; }
void Process::incrementProcessedTime() { processedTime++; }
int Process::getPID() { return PID; }
int Process::getArrivalTime() { return arrivalTime; }
int Process::getCpuBurstTime() { return cpuBurstTime; }
int Process::getProcessedTime(){ return processedTime; }
int Process::getIoBurstTime() { return ioBurstTime; }
int Process::getCompletionTime() { return completionTime; }