#include "Profiler.h"
#ifdef PROFILING_ON
#include <cassert>
#include <fstream>
#endif // profiling on

using typedefz::uint; //<--why use this here? its a narrow scope
//on for this cpp file.

namespace Profiling
{

	Profiler Profiler::theInstance;
	Profiler& Profiler::getInstance()
	{
		return theInstance;
	}

#ifdef PROFILING_ON

	static std::ofstream outStream; //<---static makes private to this .cpp

	void Profiler::shutdown()
	{
		writeData();
	}
	void Profiler::initialize(const char* filename)
	{
		this->fileName = filename;
		frameIndex = -1;
		categoryIndex = 0;
		numUsedCategories = 0;
	}
	void Profiler::addEntry(const char* category, float time)
	{

		assert(categoryIndex < MAX_PROFILE_CATS);
		ProfileCategory& pc = categories[categoryIndex];

		if (frameIndex == 0)
		{
			pc.name = category;
			numUsedCategories++;
		}
		else
		{
			assert(pc.name == category && category != NULL);
			assert(categoryIndex < numUsedCategories);
		}

		categoryIndex++;
		pc.sample[frameIndex % MAX_FRAME_SAMPLE] = time;

	}
	void Profiler::newFrame()
	{
		if (frameIndex > 0)
		{
			assert(categoryIndex == numUsedCategories);
		}
		frameIndex++;
		categoryIndex = 0;


	}
	char Profiler::getDelim(uint index) const
	{
		return ((index + 1) < numUsedCategories) ? ',' : '\n';
	}
	uint Profiler::getMaxFrameSample() const
	{
		return MAX_FRAME_SAMPLE;
	}
	bool Profiler::wrapped() const
	{
		return frameIndex >= MAX_FRAME_SAMPLE && frameIndex != -1;
	}
	void Profiler::writeFrame(uint frameNumber) const
	{
		for (uint cat = 0; cat < numUsedCategories; cat++)
		{
			outStream << categories[cat].sample[frameNumber];
			outStream << getDelim(cat);
		}

	}
	void Profiler::writeData() const
	{
		outStream.open(fileName, std::ios::trunc);

		//category headers
		for (uint i = 0; i < numUsedCategories; i++)
		{
			outStream << categories[i].name;
			outStream << getDelim(i);
		}

		uint endIndex;
		uint startIndex;

		///have we wrapped around the circular array? the logic below this handles that
		if (wrapped())
		{
			//0 % 5 = 0, 2 % 5 = 2
			endIndex = frameIndex % MAX_FRAME_SAMPLE;

			//example 4 % 5 = 4 + 1 = 5 % 5 = 0 which is the beginning of the frame sampling
			startIndex = (endIndex + 1) % MAX_FRAME_SAMPLE;


			while (startIndex != endIndex)
			{
				writeFrame(startIndex);

				startIndex = (startIndex + 1) % MAX_FRAME_SAMPLE;
			}

			//full frame = has to meet all entries for categories
			//if it is a complete frame(3 cats written...WRITE IT)
			//if not -> dont write it 
			if (currentFrameComplete())
				writeFrame(startIndex);
		}
		else
		{
			//the array did not wrap
			uint numActualFrames = frameIndex;
			if (currentFrameComplete())
			{
				numActualFrames++;
			}

			startIndex = 0;
			endIndex = numActualFrames;

			while (startIndex < endIndex)
			{
				writeFrame(startIndex++);

			}

		}

		outStream.close();

	}
	bool Profiler::currentFrameComplete() const
	{
		return categoryIndex == numUsedCategories;
	}

}
#endif

