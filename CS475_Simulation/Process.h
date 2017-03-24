#ifndef PROCESS_H_
#define PROCESS_H_

class Process {
private:
	static int PIDcounter;
	int PID;
	int arrivalTime;
	int cpuBurstTime1;
	int cpuBurstTime2;
	int processedTime;
	int startWaitTime;
	int waitTime;
	int ioTime;
	int ioBurstTime1;
	int ioBurstTime2;
	int completionTime;
	int responseTime;
public:
	Process() {
		PID = PIDcounter;
		PIDcounter++;
	}

	Process(int arrivalTime, int cpuBurstTime1, int cpuBurstTime2, int ioBurstTime1, int ioBurstTime2) {
		PID = PIDcounter;
		PIDcounter++;
		this->arrivalTime = arrivalTime;
		this->cpuBurstTime1 = cpuBurstTime1;
		this->cpuBurstTime2 = cpuBurstTime2;
		this->ioBurstTime1 = ioBurstTime1;
		this->ioBurstTime2 = ioBurstTime2;
		processedTime = 0;
		ioTime = 0;
		startWaitTime = 0;
	}

	void setCompletionTime(int completionTime);
	void incrementProcessedTime();
	void incrementIoTime();
	void setStartWaitTime(int startWaitTime);
	void setWaitTime(int waitTime);
	void setResponseTime(int responseTime);
	int getPID();
	int getArrivalTime();
	int getCpuBurstTime1();
	int getCpuBurstTime2();
	int getProcessedTime();
	int getIoTime();
	int getIoBurstTime1();
	int getIoBurstTime2();
	int getCompletionTime();
	int getWaitTime();
	int getStartWaitTime();
	int getResponseTime();
};

#endif