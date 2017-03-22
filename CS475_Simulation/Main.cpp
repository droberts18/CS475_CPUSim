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
	// TO DO: add incoming random processes to vector
	ifstream file("DataFile.csv");
	string line;
	string arrivalTime;
	string CPUBurstTime;
	string IOBurstTime;
	int i = 1;

	//while (getline(file, line)) {
	//	if (i > 1) {
	//		getline(getline(sst, , ','), lastname, ',');
	//	}
	//}

	for (int i = 0; i < 1000; i++) {
		incomingProcesses.push_back(new Process(0, 1, 0));
	}
	CPU c = CPU();
	//c.runFCFS(incomingProcesses);

	int quantum;
	do {
		cout << "Please enter the desired quantum for RR: ";
		cin >> quantum;
	} while (quantum <= 0);
	//c.runRR(incomingProcesses, quantum);

	return 0;
}