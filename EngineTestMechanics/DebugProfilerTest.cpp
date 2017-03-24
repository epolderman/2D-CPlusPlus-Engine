#include <Profiler.h>
#include <gtest\gtest.h>
#include <fstream>
using std::ifstream;
using std::string;

//can make a static(private to this cpp unit)
//an un named namespace also makes this private via the cpp


///static really manes compile time
namespace
{
	
	const char* categories[] = { "Category1", "Category2", "Category3" };

	const char* const PROFILE_NAME = "profilerdata.csv";

	const unsigned int NUM_CATEGORIES = sizeof(categories) / sizeof(*categories);

	//write samples to the file
	void writeSamples(unsigned int numFrames)
	{

		float sampleNumber = 0;

		for (unsigned int i = 0; i < numFrames; i++)
		{

			Pro.newFrame();
			for (unsigned int cat = 0; cat < NUM_CATEGORIES; cat++)
			{
				Pro.addEntry(categories[cat], sampleNumber++);
			}

		}


	}

	//checking end of file and the last character after the end of file
	bool atEndofFile(ifstream& input)
	{
		if (!input.good())
		{
			return false;
		}
		//trying to read past the last bit in the file
		char lastbit;
		input >> lastbit;
		return !input.good();
	}

	/* no skip white space does not skip the white spaces in the file stream */
	string getNextToken(ifstream& file)
	{
		char c;
		string buffer;
		while (file.good())
		{
			file >> std::noskipws;
			file >> c;
			if (c == ',' || c == '\n')
				break;
			buffer += c;

		}

		return buffer;
	}

	//check for sample profiles
	void checkSamples(unsigned int numFrames, bool excludeLastFrame = false)
	{
		ifstream input(PROFILE_NAME);

		for (unsigned int i = 0; i < NUM_CATEGORIES; i++)
		{
			EXPECT_EQ(getNextToken(input), categories[i]);
		}

		//profileNumber = what samples we are on sample 0 , 1 , 2 = in frame 1
		unsigned int profileNumber = 0;
		//if numFrames(max frame 8) - maxFramesWeCanStore(5) * number of Categories
		if (numFrames >= Pro.getMaxFrameSample())
		{
			profileNumber = (numFrames - Pro.getMaxFrameSample()) * NUM_CATEGORIES;
			numFrames = Pro.getMaxFrameSample();
		}

		if (excludeLastFrame)
		{
			profileNumber += NUM_CATEGORIES;
			numFrames--;
		}


		for (unsigned int i = 0; i < (numFrames * NUM_CATEGORIES); i++)
		{
			string buffer = getNextToken(input);
			unsigned int number = atoi(buffer.c_str());
			EXPECT_EQ(number, profileNumber++);
		}

		EXPECT_TRUE(atEndofFile(input));
	}


	void runTestsOnFrames(unsigned int numFrames)
	{
		Pro.initialize(PROFILE_NAME);
		const unsigned int NUM_SAMPLES_THIS_TEST = 5;
		writeSamples(numFrames);
		Pro.shutdown();
		checkSamples(numFrames);
	}
	
	void writeIncompleteFrames(unsigned int numFrames)
	{
		bool wrapped = numFrames >= Pro.getMaxFrameSample();
		Pro.initialize(PROFILE_NAME);

		writeSamples(numFrames);

		Pro.newFrame();

		Pro.addEntry(categories[0], 15);

		Pro.shutdown();

		//checkFrames
		checkSamples(numFrames, wrapped);

		//	//

		Pro.initialize(PROFILE_NAME);

		writeSamples(numFrames);

		Pro.newFrame();

		Pro.addEntry(categories[0], 15);

		Pro.addEntry(categories[1], 16);

		Pro.shutdown();

		checkSamples(numFrames, wrapped);
	}
}


TEST(Profiler, SampleProfiler)
{

	//Pro.initialize(PROFILE_NAME);

	//const unsigned int NUM_FRAMES_THIS_TEST = 5;

	//writeSamples(NUM_FRAMES_THIS_TEST);

	//checkSamples(NUM_FRAMES_THIS_TEST);

	//Pro.shutdown();


}
TEST(Profiler, PartialFullFrameTests)
{
	writeIncompleteFrames(Pro.getMaxFrameSample() -2); //do not wrap
	writeIncompleteFrames(Pro.getMaxFrameSample() + 2); //wrap
}
TEST(Profiler, smallAmountNonCIRC)
{
	runTestsOnFrames(5);
}
TEST(Profiler, largeAmountNonCIRC)
{
	///static cast = compile time cast
	const unsigned int NUM_FRAMES_DIS = static_cast<unsigned int>(Pro.getMaxFrameSample() * .8);
	runTestsOnFrames(NUM_FRAMES_DIS);
}
TEST(Profiler, ArrayBoundaries)
{
	runTestsOnFrames(Pro.getMaxFrameSample());
	runTestsOnFrames(Pro.getMaxFrameSample() + 1);
	runTestsOnFrames(Pro.getMaxFrameSample() + 2);
}
TEST(Profiler, CirculatingOnePlusSome)
{
	const unsigned int NUM_FRAMES_DIS = static_cast<unsigned int>(Pro.getMaxFrameSample() + 3);
	runTestsOnFrames(NUM_FRAMES_DIS);
}
TEST(Profiler, fullCircular)
{
	const unsigned int NUM_FRAMES_DIS = static_cast<unsigned int>(Pro.getMaxFrameSample() * 3.141562);
	runTestsOnFrames(NUM_FRAMES_DIS);
}
//TEST(Profiler, AddingDuplicateCategoriesinOneFrame)
//{
//
//	Pro.initialize(PROFILE_NAME);
//	Pro.newFrame();
//	Pro.addEntry("My First Cat", 1);
//	Pro.addEntry("My Second Category", 1);
//	Pro.addEntry("My First Cat", 2);
//	Pro.shutdown();
//
//}

