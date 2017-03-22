#include "CPU.h"
#include <iostream>

void CPU::checkForIncomingProcesses(vector<Process*> processes, int clock) {
	for (int i = 0; i < processes.size(); i++) {
		if (processes[i]->getArrivalTime() == clock) {
			if (processes[i]->getIoBurstTime() != 0)
				waitingQueue.push(processes[i]);
			else
				readyQueue.push(processes[i]);

			std::swap(processes[i], processes.back());
			processes.pop_back();
		}
	}
}

void CPU::run(vector<Process*> processes) {
	int numCompletedProcesses = 0;
	
	do {
		checkForIncomingProcesses(processes, clock);
		if (waitingQueue.size() > 0) {
			if (waitingQueue.front()->getIoBurstTime() <= clock-waitingQueue.front()->getArrivalTime()) {
				readyQueue.push(waitingQueue.front());
				waitingQueue.pop();
			}
		}
		if (currentProcess == NULL) {
			currentProcess = readyQueue.front();
			readyQueue.pop();
		}
		else if (currentProcess->getCpuBurstTime() <= clock-readyQueue.front()->getIoBurstTime()-readyQueue.front()->getArrivalTime()) {
			currentProcess->setCompletionTime(clock);
			completedProcesses.push_back(currentProcess);
			currentProcess = NULL;
			numCompletedProcesses++;
		}
		clock++;
	} while (numCompletedProcesses < 2);
}