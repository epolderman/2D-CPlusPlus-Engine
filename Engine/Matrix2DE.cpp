#include "Matrix2DE.h"


//vector * matrix (optimization is here)
Vector3D Matrix2DE::operator*(const Vector3D vector) const
{

	return Vector3D
		(
		(vector.getX() * this->r0c0 + vector.getY() * this->r0c1 + vector.getZ() * this->r0c2),
		(vector.getX() * this->r1c0 + vector.getY() * this->r1c1 + vector.getZ() * this->r1c2), vector.getZ());

}
//rotate around an angle in 3D
Matrix2DE Matrix2DE::rotateZ(float radians)
{

	float cosResult = cos(radians);
	float sinResult = sin(radians);

	return Matrix2DE(cosResult, -sinResult, 0,
					 sinResult, cosResult, 0);

}

//identity matrix with the x and y in the z basis vector 
//(putting the vectors in the z plane and translating them(moving them all at once)
Matrix2DE Matrix2DE::translate(float xx, float yy)
{				// x basis, y basis, z basis vectors
	return Matrix2DE(1, 0, xx,
					 0, 1, yy);
}
Matrix2DE Matrix2DE::translate(const Vector3D& position)
{
	return translate(position.getX(), position.getY());
}

//matrix * matrix multiplication
Matrix2DE Matrix2DE::operator*(const Matrix2DE mat)
{
	return Matrix2DE
		(

		r0c0 * mat.r0c0 + r0c1 * mat.r1c0,
		r0c0 * mat.r0c1 + r0c1 * mat.r1c1,
		r0c0 * mat.r0c2 + r0c1 * mat.r1c2 + r0c2,

		r1c0 * mat.r0c0 + r1c1 * mat.r1c0,
		r1c0 * mat.r0c1 + r1c1 * mat.r1c1,
		r1c0 * mat.r0c2 + r1c1 * mat.r1c2 + r1c2);

}


Matrix2DE Matrix2DE::scale(float x, float y)
{

	return Matrix2DE(x, 0, 0,
					0, y, 0);

}