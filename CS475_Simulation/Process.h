#ifndef PROCESS_H_
#define PROCESS_H_

class Process {
private:
	static int PIDcounter;
	int PID;
	int arrivalTime;
	int cpuBurstTime;
	int processedTime;
	int ioBurstTime;
	int completionTime;
public:
	Process() {
		PID = PIDcounter;
		PIDcounter++;
	}

	Process(int arrivalTime, int cpuBurstTime, int ioBurstTime) {
		PID = PIDcounter;
		PIDcounter++;
		this->arrivalTime = arrivalTime;
		this->cpuBurstTime = cpuBurstTime;
		this->ioBurstTime = ioBurstTime;
		processedTime = 0;
	}

	void setCompletionTime(int completionTime);
	void incrementProcessedTime();
	int getPID();
	int getArrivalTime();
	int getCpuBurstTime();
	int getProcessedTime();
	int getIoBurstTime();
	int getCompletionTime();
};

#endif