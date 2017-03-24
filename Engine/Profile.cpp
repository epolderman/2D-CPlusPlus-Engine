#if PROFILING_ON
#include "Profile.h"
#include "Profiler.h"

namespace Profiling
{
	Profile::Profile(const char * category) : category(category)
	{
		clock.initialize();
		clock.start();
	}
	Profile::~Profile()
	{
		clock.stop();
		Pro.addEntry(category, clock.lastLapTime());
	}
}
#endif