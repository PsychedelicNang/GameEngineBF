#include "FPSInformation.h"

FPSInformation::FPSInformation()
{
	m_fps = 0;
	m_frameCount = 0;
	m_elapsedTime = 0.f;
}

FPSInformation::~FPSInformation()
{
}

void FPSInformation::Initialize()
{
	m_fps = 0;
	m_frameCount = 0;
	m_elapsedTime = 0.f;
}

void FPSInformation::Update(float _deltaTime)
{
	m_elapsedTime += _deltaTime;
	m_frameCount++;

	if (m_elapsedTime >= 1.f)
	{
		m_fps = m_frameCount;
		m_frameCount = 0;
		m_elapsedTime = 0.f;
	}
}

int FPSInformation::GetFps()
{
	return m_fps;
}
