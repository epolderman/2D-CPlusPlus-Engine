#ifndef GAME_CLOCK_H
#define GAME_CLOCK_H
#include "Clock.h"



class _declspec(dllexport) GameClock
{
	Clock clock;
	//needed for singleton
	//1.make constructor private
	GameClock() { }
	//2. make copy constructor private & not implement it
	GameClock(const GameClock&);
	//3. make assignment operator private
	GameClock& operator=(const GameClock&);
	//4.instance (memory of this instance is in .cpp)
	static GameClock instance;
	//needed for singleton
public:
	bool initialize();
	bool shutdown();
	void newFrame();
	float dt() const;
	static GameClock& getInstance();
};

#define gameClock GameClock::getInstance()

#endif