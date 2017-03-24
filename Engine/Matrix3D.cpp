#include "Matrix3D.h"


//vector * matrix
Vector3D Matrix3D::operator*(const Vector3D vector)
{

	return Vector3D
		(
		(vector.getX() * this->r0c0 + vector.getY() * this->r0c1 + vector.getZ() * this->r0c2),
		(vector.getX() * this->r1c0 + vector.getY() * this->r1c1 + vector.getZ() * this->r1c2),
		(vector.getX() * this->r2c0 + vector.getY() * this->r2c1 + vector.getZ() * this->r2c2)
		);

}

//rotate around an angle in 3D
Matrix3D Matrix3D::rotateZ(float radians)
{

	float cosResult = cos(radians);
	float sinResult = sin(radians);

	return Matrix3D(cosResult, -sinResult, 0,
					sinResult, cosResult, 0,
					0, 0, 1);

}


//identity matrix with the x and y in the z basis vector 
//(putting the vectors in the z plane and translating them(moving them all at once)
Matrix3D Matrix3D::translate(float xx, float yy)
{				// x basis, y basis, z basis vectors
	return Matrix3D(1, 0, xx,
					0, 1, yy,
					0, 0, 1);
}


//matrix * matrix multiplication
Matrix3D Matrix3D::operator*(const Matrix3D mat)
{
	return Matrix3D
		(
		r0c0 * mat.r0c0 + r0c1 * mat.r1c0 + r0c2 * mat.r2c0,
		r0c0 * mat.r0c1 + r0c1 * mat.r1c1 + r0c2 * mat.r2c1,
		r0c0 * mat.r0c2 + r0c1 * mat.r1c2 + r0c2 * mat.r2c2,

		r1c0 * mat.r0c0 + r1c1 * mat.r1c0 + r1c2 * mat.r2c0,
		r1c0 * mat.r0c1 + r1c1 * mat.r1c1 + r1c2 * mat.r2c1,
		r1c0 * mat.r0c2 + r1c1 * mat.r1c2 + r1c2 * mat.r2c2,

		r2c0 * mat.r0c0 + r2c1 * mat.r1c0 + r2c2 * mat.r2c0,
		r2c0 * mat.r0c1 + r2c1 * mat.r1c1 + r2c2 * mat.r2c1,
		r2c0 * mat.r0c2 + r2c1 * mat.r1c2 + r2c2 * mat.r2c2
		);

}

Matrix3D Matrix3D::scale(float x, float y)
{
	return Matrix3D(x, 0, 0,
					0, y, 0,
					0, 0, 1);

}


