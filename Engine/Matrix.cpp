#include "Matrix.h"

//return value optimization


Matrix::Matrix(float tl, float tr, float bl, float br)
{
	this->topleft = tl;
	this->topright = tr;
	this->bottomleft = bl;
	this->bottomright = br;
}
//vector * matrix
Vector Matrix::operator*(const Vector& vector)
{
	return Vector(
		(vector.getX() * this->topleft)
		+ (vector.getY() * this->topright),

		(vector.getX() * this->bottomleft)
		+ (vector.getY() * this->bottomright) 
		);
}
//rotation matrix depending on angle pass in
Matrix Matrix::rotate(float radians)
{
	float cosResult = cos(radians);
	float sinResult = sin(radians);

	return Matrix(cosResult, -sinResult,
				  sinResult, cosResult);

}
