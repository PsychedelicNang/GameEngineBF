#pragma once
/***************************
* Filename: CPUInformation.h
***************************/
#ifndef _CPUINFORMATION_H_
#define _CPUINFORMATION_H_

/***************************
* LINKING
/***************************/
#pragma comment(lib, "pdh.lib")

/***************************
* INCLUDES
***************************/
#include <pdh.h>

class CPUInformation
{
public:
	CPUInformation();
	~CPUInformation();

	void Initialize();
	void Shutdown();
	void Update();
	int GetCpuPercentage();

private:
	bool m_canReadCpu;
	HQUERY m_queryHandle;
	HCOUNTER m_counterHandle;
	unsigned m_tickCount;
	int m_cpuUsage;
};

#endif //!_CPUINFORMATION_H_