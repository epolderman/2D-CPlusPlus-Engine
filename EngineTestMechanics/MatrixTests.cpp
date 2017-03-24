#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest\gtest.h>
#include <Matrix.h>
#include <Matrix3D.h>
#include <Matrix2DE.h>



//ALL MATRIX TESTS

//2D
TEST(Matrix, MatrixConstuctor)
{

	Matrix ident;
	EXPECT_FLOAT_EQ(ident.topleft, 1.0f);
	EXPECT_FLOAT_EQ(ident.topright, 0.0f);
	EXPECT_FLOAT_EQ(ident.bottomleft, 0.0f);
	EXPECT_FLOAT_EQ(ident.bottomright, 1.0f);


}
TEST(Matrix, MatrixMultiply)
{
	Matrix op(2, -3,
		4, 5);

	Vector victim(3, 9);

	Vector vict = op * victim;

	EXPECT_FLOAT_EQ(vict.getX(), -21.0f);
	EXPECT_FLOAT_EQ(vict.getY(), 57.0f);


}
TEST(Matrix, MatrixRotation)
{
	Matrix op;

	op = Matrix::rotate(0);
	EXPECT_FLOAT_EQ(op.topleft, 1.0);
	EXPECT_FLOAT_EQ(op.topright, 0.0);
	EXPECT_FLOAT_EQ(op.bottomleft, 0.0);
	EXPECT_FLOAT_EQ(op.bottomright, 1.0);

}
//3D
TEST(Matrix3D, Matrix3DMultiply)
{
	Matrix3D mat(1,2,3,4,5,6,7,8,9);
	Vector3D vec(2, 1, 3);

	Vector3D blue = mat * vec;

	EXPECT_FLOAT_EQ(blue.getX(), 13);
	EXPECT_FLOAT_EQ(blue.getY(), 31);
	EXPECT_FLOAT_EQ(blue.getZ(), 49);

}
TEST(Matrix3D, Matrix3DConstructor)
{
	Matrix3D identity;

	EXPECT_FLOAT_EQ(1.0, identity.r0c0);
	EXPECT_FLOAT_EQ(0.0, identity.r0c1);
	EXPECT_FLOAT_EQ(0.0, identity.r0c2);
	EXPECT_FLOAT_EQ(0.0, identity.r1c0);
	EXPECT_FLOAT_EQ(1.0, identity.r1c1);
	EXPECT_FLOAT_EQ(0.0, identity.r1c2);
	EXPECT_FLOAT_EQ(0.0, identity.r2c0);
	EXPECT_FLOAT_EQ(0.0, identity.r2c1);
	EXPECT_FLOAT_EQ(1.0, identity.r2c2);

	Matrix3D mat(1, 2, 3, 4, 5, 6, 7, 8, 9);

	EXPECT_FLOAT_EQ(1.0, mat.r0c0);
	EXPECT_FLOAT_EQ(2.0, mat.r0c1);
	EXPECT_FLOAT_EQ(3.0, mat.r0c2);
	EXPECT_FLOAT_EQ(4.0, mat.r1c0);
	EXPECT_FLOAT_EQ(5.0, mat.r1c1);
	EXPECT_FLOAT_EQ(6.0, mat.r1c2);
	EXPECT_FLOAT_EQ(7.0, mat.r2c0);
	EXPECT_FLOAT_EQ(8.0, mat.r2c1);
	EXPECT_FLOAT_EQ(9.0, mat.r2c2);
	
}
TEST(Matrix3D, Matrix3DRotation)
{
	Matrix3D op;

	op = Matrix3D::rotateZ(0);
	EXPECT_FLOAT_EQ(op.r0c0, 1.0);
	EXPECT_FLOAT_EQ(op.r0c1, 0.0);
	EXPECT_FLOAT_EQ(op.r0c2, 0.0);
	EXPECT_FLOAT_EQ(op.r1c0, 0.0);
	EXPECT_FLOAT_EQ(op.r1c1, 1.0);
	EXPECT_FLOAT_EQ(op.r1c2, 0.0);
	EXPECT_FLOAT_EQ(op.r2c0, 0.0);
	EXPECT_FLOAT_EQ(op.r2c1, 0.0);
	EXPECT_FLOAT_EQ(op.r2c2, 1.0);


}
TEST(Matrix3D, Matrix3DTranslation)
{

	Matrix3D translator = Matrix3D::translate(4, 8);
	Vector3D victim(-3,8,1);

	Vector3D victimPrime = translator * victim;

	EXPECT_FLOAT_EQ(victimPrime.getX(), 1);
	EXPECT_FLOAT_EQ(victimPrime.getY(), 16);
	EXPECT_FLOAT_EQ(victimPrime.getZ(), 1);


}
TEST(Matrix3D, Matrix3DTimesMatrix3D)
{

	Matrix3D translator(1, 0, 4, 0, 1, 8, 0, 0, 1);
	Matrix3D identity;

	Matrix3D victim = translator * identity;

	EXPECT_FLOAT_EQ(victim.r0c0, 1);
	EXPECT_FLOAT_EQ(victim.r0c1, 0);
	EXPECT_FLOAT_EQ(victim.r0c2, 4);

	EXPECT_FLOAT_EQ(victim.r1c0, 0);
	EXPECT_FLOAT_EQ(victim.r1c1, 1);
	EXPECT_FLOAT_EQ(victim.r1c2, 8);

	EXPECT_FLOAT_EQ(victim.r2c0, 0);
	EXPECT_FLOAT_EQ(victim.r2c1, 0);
	EXPECT_FLOAT_EQ(victim.r2c2, 1);

	

}
template<class T>
void testScale()
{
	Vector3D victim(6.0f, 5.0f);
	T op = T::scale(0.5f, 2.0f);
	Vector3D prime = op * victim;

	EXPECT_FLOAT_EQ(prime.getX(), 3.0f);
	EXPECT_FLOAT_EQ(prime.getY(), 10.0f);
}
TEST(Matrix3D, Matrix3DScaling)
{
	testScale<Matrix2DE>();
	testScale<Matrix3D>();

}
