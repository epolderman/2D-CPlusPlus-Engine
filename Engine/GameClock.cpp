#include "GameClock.h"




//memory of gameclock will be located in the data segment/program image/compilation unit
GameClock GameClock::instance; //<---here

bool GameClock::initialize()
{
	return clock.initialize();
}
bool GameClock::shutdown()
{
	return clock.shutdown();
}
void GameClock::newFrame()
{
	clock.lap();
}
float GameClock::dt() const
{
	return clock.lastLapTime();
}
GameClock& GameClock::getInstance()
{
	return instance;
}