#ifndef ENGLINE_CLOCK_H
#define ENGINE_CLOCK_H
#include <Windows.h>


class _declspec(dllexport) Clock
{
	//64 bits
	LARGE_INTEGER timeFreq;
	LARGE_INTEGER lastStartTime;
	LARGE_INTEGER deltaLastLap;
	float deltaTime;
	public:
		bool initialize();
		bool shutdown();
		void start();
		void stop();
		void lap();
		float lastLapTime() const;
	};




#endif