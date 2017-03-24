#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H
#include "Typedefs.h"

//static makes a value a compile time value
//compiler needs to know these values at compile time

//making MAX_FRAME_SAMPLE const without a getter and public -> makes anywhere where
//we use the const re compile where we consume this value
//GETTER allows us to grab dynamically const without recompiling
//accessing the const would be handled by some runtime code

//framesIndex = variable that goes round and round
//max frames samples = array indexes

//purpose of a namespace is to avoid name clashes

namespace Profiling
{

	class _declspec(dllexport) Profiler
	{
	public:
#if PROFILING_ON
		void addEntry(const char* category, float time);
		void newFrame();
		void shutdown();
		void initialize(const char* filename);
		typedefz::uint getMaxFrameSample() const;
		static Profiler& getInstance();
#else
		void addEntry(const char* category, float time){}
		void newFrame() {}
		void shutdown() {}
		void initialize(const char* filename) {}
		uint getMaxFrameSample() const;
#endif
	private:
		//C++ will define an assignment operator and a copy constructor if YOU do not define one
		Profiler(){}
		//disallowing copy constuct and assignment operator
		//declared this but DO NOT define it
		//guarding this class from outside users and myself as well
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler theInstance;
#if PROFILING_ON
		static const typedefz::uint MAX_FRAME_SAMPLE = 1000;
		const char* fileName;
		static const typedefz::uint MAX_PROFILE_CATS = 20;
		typedefz::uint frameIndex;
		typedefz::uint categoryIndex;
		typedefz::uint numUsedCategories;
		char getDelim(typedefz::uint index) const;
		bool wrapped() const;
		void writeFrame(typedefz::uint frameNumber) const;
		void writeData() const;
		bool currentFrameComplete() const;

		struct ProfileCategory
		{
			const char * name;
			float sample[MAX_FRAME_SAMPLE];

		} categories[MAX_PROFILE_CATS];

#endif
	};

//macro -> namespace -> class name -> get singleton
#define Pro Profiling::Profiler::getInstance()

}
#endif