#include <gtest\gtest.h>
#include <Clock.h>
#include <qt\qtest.h>
#include <iostream>
using namespace std;



//TEST(Clock, INITZ)
//{
//	Clock clock;
//	EXPECT_TRUE(clock.initialize());
//	clock.shutdown();
//}
//
//TEST(Clock, FrameTimeMeasuring)
//{
//	Clock clock;
//	EXPECT_TRUE(clock.initialize());
//	Sleep(1000); //pause execution
//	clock.lap();
//	float timedTime = clock.lastLapTime();
//	EXPECT_TRUE(0.9f < timedTime && timedTime < 1.1f);
//	clock.lap();
//
//	Sleep(500);
//	clock.lap();
//	timedTime = clock.lastLapTime();
//	EXPECT_TRUE(0.4f < timedTime && timedTime < 0.6f);
//
//	const int NUM_RANDS = 10 + rand() % 100;
//	const float THRESH_HOLD = 0.01f;
//
//		for (int i = 0; i < NUM_RANDS; i++)
//		{
//			cout << ".";
//			int thisMilis = rand() % 10000;
//			float thisTestSeconds = thisMilis / 1000.0f;
//			clock.lap();
//			Sleep(thisMilis);
//			clock.lap();
//			float elapsedSeconds = clock.lastLapTime();
//			EXPECT_TRUE(thisTestSeconds - THRESH_HOLD < elapsedSeconds &&
//				elapsedSeconds < (thisTestSeconds + THRESH_HOLD));
//			
//		}
//
//	clock.lap();
//	clock.lastLapTime();
//	EXPECT_TRUE(clock.shutdown());
//
//}