#include <gtest\gtest.h>
#include <Vector.h>
#include <Vector3D.h>

//ALL VECTOR TESTS

//2D
TEST(Vector, ConstructorClassTest)
{
	Vector yes(2, 2);
	EXPECT_EQ(2, yes.getX());
}
TEST(Vector, Scalar)
{
	Vector first(-7, 3);
	Vector result = first * 8;
	EXPECT_EQ(-56, result.getX());
	EXPECT_EQ(24, result.getY());
}
TEST(Vector, dotproduct)
{
	Vector first(10, -10);
	Vector second(10, 10);
	float value = first.DotProduct(second);
	EXPECT_EQ(0, value);
}

//3D
TEST(Vector3D, Constructor3D)
{

	Vector3D Tester(-4.3f, 4.5f, 5.9f);
	EXPECT_FLOAT_EQ(Tester.getX() ,- 4.3f);
	EXPECT_FLOAT_EQ(4.5f, Tester.getY());
	EXPECT_FLOAT_EQ(5.9f, Tester.getZ());

	Vector3D defaultConstructor;
	EXPECT_FLOAT_EQ(0.0f, defaultConstructor.getX());
	EXPECT_FLOAT_EQ(0.0f, defaultConstructor.getY());
	EXPECT_FLOAT_EQ(0.0f, defaultConstructor.getY());


}
TEST(Vector3D, MultiplicationScalar3D)
{
	Vector3D Tester(-4.3f, 4.5f, 5.9f);
	float scalar = 0.5f;

	Vector3D yahs = Tester * scalar;

	EXPECT_FLOAT_EQ(-2.15, yahs.getX());
	EXPECT_FLOAT_EQ(2.25, yahs.getY());
	EXPECT_FLOAT_EQ(2.95, yahs.getZ());


}
TEST(Vector3D, Subtraction)
{
	Vector3D first(0, 0, 0);
	Vector3D second(1, 1, 1);
	Vector3D result = first - second;
	EXPECT_FLOAT_EQ(result.getX(), -1.0);
	EXPECT_FLOAT_EQ(result.getY(), -1.0);
	EXPECT_FLOAT_EQ(result.getZ(), -1.0);
	result = second - first;
	EXPECT_FLOAT_EQ(result.getX(), 1.0);
	EXPECT_FLOAT_EQ(result.getY(), 1.0);
	EXPECT_FLOAT_EQ(result.getZ(), 1.0);
}
TEST(Vector3D, PerpinDicular)
{

	Vector3D original(4, 2,0);
	Vector3D perpClockWise = original.ClockWisePerpindicular();
	Vector3D perpCounterClockWise = original.CounterClockWisePerp();

	EXPECT_FLOAT_EQ(perpClockWise.getX(), 2);
	EXPECT_FLOAT_EQ(perpClockWise.getY(), -4);

	EXPECT_FLOAT_EQ(perpCounterClockWise.getX(), -2);
	EXPECT_FLOAT_EQ(perpCounterClockWise.getY(), 4);

}
TEST(Vector3D, DotProduct)
{

	Vector3D or(1, 1, 1);
	Vector3D yee(-1, -5, 0);

	float value = or.Dot(yee);
	EXPECT_FLOAT_EQ(value, -6.0);

}
TEST(Vector3D, LengthMagnitude)
{
	Vector3D tester(2, 5, 6);
	float magnitude = tester.Length();
	EXPECT_FLOAT_EQ(magnitude, sqrt(4 + 25 + 36));

}
TEST(Vector3D, MagnitudeSquared)
{
	Vector3D tester(2, 5, 6);
	float mag = tester.Length();
	float magnitude = tester.magnitudeSquared();
	EXPECT_FLOAT_EQ( mag * mag, magnitude );

}
TEST(Vector3D, Normalized)
{
	Vector3D first(1.0f, 2.0f, 3.0f);
	Vector3D normalized = first.Normalize();
	EXPECT_FLOAT_EQ(normalized.Length(), 1.0f);

	EXPECT_FLOAT_EQ(normalized.getX(), 1.0f / sqrt(14));
	EXPECT_FLOAT_EQ(normalized.getY(), 2.0f / sqrt(14));
	EXPECT_FLOAT_EQ(normalized.getZ(), 3.0f / sqrt(14));
}
TEST(Vector3D, ProjectOnto)
{
	Vector3D first(2, 4);
	Vector3D target(1, 0);
	Vector3D result = first.projectOnto(target);
	EXPECT_FLOAT_EQ(result.getX(), 2.0f);
	EXPECT_FLOAT_EQ(result.getY(), 0.0f);
	EXPECT_FLOAT_EQ(result.getZ(), 0.0f);

}
TEST(Vector3D, AngleProjectOntoTest)
{
	//unit circle cos theta test
	Vector3D a(0.5f, sqrt(3) / 2); //60 degrees pi/3
	Vector3D b(sqrt(3) / 2, 0.5f); //30 degrees pi/6
	float dotR = a.Dot(b);
	EXPECT_FLOAT_EQ(dotR, cos(3.1415926535897932846f / 6.0f));
}
TEST(Vector3D, Lerp)
{
	Vector3D source(1.0f, 2.0f, 3.0f);
	Vector3D target(2.0f, 3.0f, 4.0f);

	Vector3D diff = target - source;
	float alpha = 0.0f;
	while (alpha <= 1.0f)
	{
		Vector3D lerpResult1 = source.lerp(alpha, target);
		Vector3D lerpResult2 = source + diff * alpha;

		EXPECT_FLOAT_EQ(lerpResult1.getX(), lerpResult2.getX());
		EXPECT_FLOAT_EQ(lerpResult1.getY(), lerpResult2.getY());
		EXPECT_FLOAT_EQ(lerpResult1.getZ(), lerpResult2.getZ());

		alpha += 0.01f;
	}

}