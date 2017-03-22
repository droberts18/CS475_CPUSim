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

void CPU::runFCFS(vector<Process*> processes) {
	vector<Process*> incomingProcesses = processes;
	int numCompletedProcesses = 0;
	clock = 0;
	
	do {
		checkForIncomingProcesses(incomingProcesses, clock);
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

		currentProcess->incrementProcessedTime();

		if (currentProcess->getCpuBurstTime() == currentProcess->getProcessedTime()) {
			currentProcess->setCompletionTime(clock);
			completedProcesses.push_back(currentProcess);
			currentProcess = NULL;
			numCompletedProcesses++;
		}
		clock++;
	} while (numCompletedProcesses < processes.size());
}

void CPU::runRR(vector<Process*> processes, int quantum) {
	vector<Process*> incomingProcesses = processes;
	int numCompletedProcesses = 0;
	clock = 0;

	do {
		checkForIncomingProcesses(incomingProcesses, clock);
		if (waitingQueue.size() > 0) {
			if (waitingQueue.front()->getIoBurstTime() <= clock - waitingQueue.front()->getArrivalTime()) {
				readyQueue.push(waitingQueue.front());
				waitingQueue.pop();
			}
		}

		if (currentProcess == NULL) {
			currentProcess = readyQueue.front();
			readyQueue.pop();
		}

		currentProcess->incrementProcessedTime();

		if (currentProcess->getCpuBurstTime() == currentProcess->getProcessedTime()) {
			currentProcess->setCompletionTime(clock);
			completedProcesses.push_back(currentProcess);
			currentProcess = NULL;
			numCompletedProcesses++;
		}

		if (currentProcess->getProcessedTime() % quantum == 0) {
			readyQueue.push(currentProcess);
			currentProcess = NULL;
		}
		clock++;
	} while (numCompletedProcesses < processes.size());
}