// Created by Zach Kinney, Zach Goold, and Drew Roberts
#include <iostream>
#include <fstream>
#include <string>
#include "Process.h"
#include "CPU.h"

using namespace std;

int Process::PIDcounter = 1;

int main() {
	vector<Process*> incomingProcesses;
	ifstream file("DataFile.csv");
	string line;
	string arrivalTime;
	string CPUBurstTime1;
	string CPUBurstTime2;
	string IOBurstTime1;
	string IOBurstTime2;
	int i = 1;

	while (getline(file, arrivalTime, ',')) {
		getline(file, CPUBurstTime1, ',');
		getline(file, IOBurstTime1, ',');
		getline(file, CPUBurstTime2, ',');
		getline(file, IOBurstTime2);
		Process *processPoint = new Process(stoi(arrivalTime), stoi(CPUBurstTime1), stoi(CPUBurstTime2), stoi(IOBurstTime1), stoi(IOBurstTime2));
		incomingProcesses.push_back(processPoint);
		processPoint = NULL;
	}

	CPU c = CPU();

	//c.runFCFS(incomingProcesses);
	// Preset quantum of 5 ms for round robin
	int quantum = 5;
	//c.runRR(incomingProcesses, quantum);

	c.runMultiFCFS(incomingProcesses);

	return 0;
}