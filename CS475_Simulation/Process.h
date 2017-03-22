#ifndef PROCESS_H_
#define PROCESS_H_

class Process {
private:
	static int PIDcounter;
	int PID;
	int arrivalTime;
	int cpuBurstTime;
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
	}

	void setCompletionTime(int completionTime);
	int getPID();
	int getArrivalTime();
	int getCpuBurstTime();
	int getIoBurstTime();
	int getCompletionTime();
};

#endif