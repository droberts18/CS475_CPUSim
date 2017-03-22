// Created by Zach Kinney, Zach Goold, and Drew Roberts
#include <iostream>
#include "Process.h"
#include "CPU.h"

using namespace std;

int Process::PIDcounter = 1;

int main() {
	vector<Process*> incomingProcesses;
	// TO DO: add incoming random processes to vector
	
	for (int i = 0; i < 1000; i++) {
		incomingProcesses.push_back(new Process(0, 1, 0));
	}
	CPU c = CPU();
	c.run(incomingProcesses);

	return 0;
}