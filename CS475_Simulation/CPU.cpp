#include "CPU.h"
#include <iostream>

void CPU::checkForIncomingProcesses(vector<Process*> processes, int clock) {
	for (int i = 0; i < processes.size(); i++) {
		if (processes[i]->getArrivalTime() == clock) {
			if (processes[i]->getIoBurstTime1() != 0)
				waitingQueue.push(processes[i]);
			else {
				processes[i]->setStartWaitTime(clock);
				readyQueue.push(processes[i]);
			}
		}
	}
}

void CPU::runFCFS(vector<Process*> processes) {
	vector<Process*> incomingProcesses = processes;
	int numCompletedProcesses = 0;
	clock = 0;
	
	do {
		checkForIncomingProcesses(incomingProcesses, clock);
		if (waitingQueue.size() > 0) {
			// increments IO time
			waitingQueue.front()->incrementIoTime();
			// checks to see if the process at the front of the waiting queue is done with its respective IO operations
			// check first IO burst, then second
			if (waitingQueue.front()->getIoBurstTime1() == waitingQueue.front()->getIoTime()) {
				// sets the start waiting time to the current time
				waitingQueue.front()->setStartWaitTime(clock);
				readyQueue.push(waitingQueue.front());
				waitingQueue.pop();
			}
			else if (waitingQueue.front()->getIoBurstTime1() + waitingQueue.front()->getIoBurstTime2() == waitingQueue.front()->getIoTime()) {
				// sets the start waiting time to the current time
				waitingQueue.front()->setStartWaitTime(clock);
				readyQueue.push(waitingQueue.front());
				waitingQueue.pop();
			}
		}
		// gets a new current process
		if (currentProcess == NULL && !readyQueue.empty()) {
			currentProcess = readyQueue.front();
			readyQueue.pop();
			// checks to see if this is the first time the process has been allocated for by the CPU
			// if so, the response time is recorded
			if (currentProcess->getProcessedTime() == 0)
				currentProcess->setResponseTime(clock - currentProcess->getArrivalTime());
			currentProcess->setWaitTime(clock - currentProcess->getStartWaitTime());
		}

		if (currentProcess != NULL) {
			// increment process time for current process, if there is one
			currentProcess->incrementProcessedTime();
			if (currentProcess->getCpuBurstTime1() == currentProcess->getProcessedTime()) {
				if (currentProcess->getIoBurstTime2() != 0) {
					waitingQueue.push(currentProcess);
					currentProcess = NULL;
				}
				else {
					currentProcess->setCompletionTime(clock);
					completedProcesses.push_back(currentProcess);
					currentProcess = NULL;
					numCompletedProcesses++;
				}
			}
			else if (currentProcess->getCpuBurstTime1() + currentProcess->getCpuBurstTime2() == currentProcess->getProcessedTime()) {
				currentProcess->setCompletionTime(clock);
				completedProcesses.push_back(currentProcess);
				currentProcess = NULL;
				numCompletedProcesses++;
			}
		}
		clock++;
	} while (numCompletedProcesses < processes.size());
	computeStats(clock);
}

void CPU::runRR(vector<Process*> processes, int quantum) {
	vector<Process*> incomingProcesses = processes;
	int numCompletedProcesses = 0;
	clock = 0;

	do {
		checkForIncomingProcesses(incomingProcesses, clock);
		if (waitingQueue.size() > 0) {
			// increments IO time
			waitingQueue.front()->incrementIoTime();
			// checks to see if the process at the front of the waiting queue is done with its respective IO operations
			// check first IO burst, then second
			if (waitingQueue.front()->getIoBurstTime1() == waitingQueue.front()->getIoTime()) {
				// sets the start waiting time to the current time
				waitingQueue.front()->setStartWaitTime(clock);
				readyQueue.push(waitingQueue.front());
				waitingQueue.pop();
			}
			else if (waitingQueue.front()->getIoBurstTime1() + waitingQueue.front()->getIoBurstTime2() == waitingQueue.front()->getIoTime()) {
				// sets the start waiting time to the current time
				waitingQueue.front()->setStartWaitTime(clock);
				readyQueue.push(waitingQueue.front());
				waitingQueue.pop();
			}
		}

		if (currentProcess == NULL && !readyQueue.empty()) {
			currentProcess = readyQueue.front();
			readyQueue.pop();
			// checks to see if this is the first time the process has been allocated for by the CPU
			// if so, the response time is recorded
			if (currentProcess->getProcessedTime() == 0)
				currentProcess->setResponseTime(clock - currentProcess->getArrivalTime());
			currentProcess->setWaitTime(clock - currentProcess->getStartWaitTime());
		}

		if (currentProcess != NULL) {
			// increments processed time, if there is a current process
			currentProcess->incrementProcessedTime();
			if (currentProcess->getCpuBurstTime1() == currentProcess->getProcessedTime()) {
				if (currentProcess->getIoBurstTime2() != 0) {
					waitingQueue.push(currentProcess);
					currentProcess = NULL;
				}
				else {
					currentProcess->setCompletionTime(clock);
					completedProcesses.push_back(currentProcess);
					currentProcess = NULL;
					numCompletedProcesses++;
				}
			}
			else if (currentProcess->getCpuBurstTime1() + currentProcess->getCpuBurstTime2() == currentProcess->getProcessedTime()) {
				currentProcess->setCompletionTime(clock);
				completedProcesses.push_back(currentProcess);
				currentProcess = NULL;
				numCompletedProcesses++;
			}
			else if (currentProcess->getProcessedTime() % quantum == 0) {
				readyQueue.push(currentProcess);
				currentProcess = NULL;
			}
		}
		clock++;
	} while (numCompletedProcesses < processes.size());
	computeStats(clock);
}

// computes all neccessary stats and outputs them to the console
void CPU::computeStats(int clock) {
	// getting throughput time (number of completed processes divided by the time it took to complete all of them)
	double throughputTime = completedProcesses.size() / clock;
	cout << "Throughput Time: " << throughputTime << " ms" << endl;

	int totalTurnaroundTime = 0;
	int totalWaitTime = 0;
	int totalResponseTime = 0;
	for (int i = 0; i < completedProcesses.size(); i++) {
		totalTurnaroundTime += (completedProcesses[i]->getCompletionTime() - completedProcesses[i]->getArrivalTime());
		totalWaitTime += completedProcesses[i]->getWaitTime();
		totalResponseTime += completedProcesses[i]->getResponseTime();
	}
	double avgTurnaroundTime = totalTurnaroundTime / completedProcesses.size();
	cout << "Average Turnaround Time: " << avgTurnaroundTime << " ms" << endl;

	double avgWaitTime = totalWaitTime / completedProcesses.size();
	cout << "Average Wait Time: " << avgWaitTime << " ms" << endl;

	double avgResponseTime = totalResponseTime / completedProcesses.size();
	cout << "Average Response Time: " << avgResponseTime << " ms" << endl;
}