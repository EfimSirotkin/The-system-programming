#pragma once
class CPULoadRetriever {
private:
	double cpuLoad;
public:
	CPULoadRetriever();
	~CPULoadRetriever();
	void RetrieveCPULoad();
	double GetCPULoad();
};