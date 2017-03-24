#include "Clock.h"

bool Clock::initialize()
{

	//will not ever change until you reboot the computer
	bool b = QueryPerformanceFrequency(&timeFreq) != 0;
	if (!b)
	{
		return false;
	}

	return QueryPerformanceCounter(&lastStartTime) != 0;
	
}
bool Clock::shutdown()
{
	return true;
}
void Clock::lap()
{
	stop();
	start();
}
void Clock::start()
{
	QueryPerformanceCounter(&lastStartTime);
}
void Clock::stop()
{
	LARGE_INTEGER thisTime;
	QueryPerformanceCounter(&thisTime);
	LARGE_INTEGER delta;
	delta.QuadPart = thisTime.QuadPart - lastStartTime.QuadPart;
	deltaTime = ((float)delta.QuadPart) / timeFreq.QuadPart;
	deltaLastLap.QuadPart = thisTime.QuadPart;
}
float Clock::lastLapTime() const
{
	return deltaTime;
}
