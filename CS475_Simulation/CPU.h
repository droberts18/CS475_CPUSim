#ifndef CPU_H_
#define CPU_H_

#include <queue>
#include <vector>
#include "Process.h"

using namespace std;

class CPU {
private:
	queue<Process*> waitingQueue;
	queue<Process*> readyQueue;
	vector<Process*> completedProcesses;
	Process* currentProcess;
	int clock;
public:
	CPU() { 
		currentProcess = NULL; 
		clock = 0;
	}

	void checkForIncomingProcesses(vector<Process*> processes, int clock);
	void run(vector<Process*> processes);
};

#endif