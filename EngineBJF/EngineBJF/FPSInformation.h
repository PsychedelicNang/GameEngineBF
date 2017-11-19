#pragma once
/***************************
* Filename: FPSInformation.h
***************************/
#ifndef _FPSINFORMATION_H_
#define _FPSINFORMATION_H_

class FPSInformation
{
public:
	FPSInformation();
	~FPSInformation();

	void Initialize();
	void Update(float _deltaTime);
	int GetFps();

private:
	int m_fps, m_frameCount;
	float m_elapsedTime;
};

#endif //!_FPSINFORMATION_H_