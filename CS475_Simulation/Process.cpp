#include "Process.h"

void Process::setCompletionTime(int completionTime){ this->completionTime = completionTime; }
void Process::incrementProcessedTime() { processedTime++; }
void Process::incrementIoTime() { ioTime++; }
void Process::setStartWaitTime(int startWaitTime) { this->startWaitTime = startWaitTime; }
void Process::setWaitTime(int waitTime) { this->waitTime += waitTime; }
void Process::setResponseTime(int responseTime) { this->responseTime = responseTime; }
int Process::getPID() { return PID; }
int Process::getArrivalTime() { return arrivalTime; }
int Process::getCpuBurstTime1() { return cpuBurstTime1; }
int Process::getCpuBurstTime2() { return cpuBurstTime2; }
int Process::getProcessedTime(){ return processedTime; }
int Process::getIoTime() { return ioTime; }
int Process::getIoBurstTime1() { return ioBurstTime1; }
int Process::getIoBurstTime2() { return ioBurstTime2; }
int Process::getCompletionTime() { return completionTime; }
int Process::getWaitTime() { return waitTime;  }
int Process::getStartWaitTime() { return startWaitTime; }
int Process::getResponseTime() { return responseTime; }