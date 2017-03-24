#ifndef ENGINE_MATRIX_2DE_H
#define ENGINE_MATRIX_2DE_H
#include "Vector3D.h"

//matrix 2D Efficient(since the bottom row of a matrix
//is not needed(for translation, rotation, and scaling
//except for the z basis vector in plane 1,
//we can make small efficient tweaks to our matrix class
//to eliminate some matrix multiplcation operations

class _declspec(dllexport) Matrix2DE
{

	//row major order
public:
	float r0c0; //top left
	float r0c1; //top mid
	float r0c2; //top right

	float r1c0; //mid left
	float r1c1; //mid mid
	float r1c2; //mid right

	//constructor
	//identity matrix
	explicit Matrix2DE(float r0c0 = 1, float r0c1 = 0, float r0c2 = 0,
		float r1c0 = 0, float r1c1 = 1, float r1c2 = 0) :
		r0c0(r0c0), r0c1(r0c1), r0c2(r0c2),
		r1c0(r1c0), r1c1(r1c1), r1c2(r1c2) {}

	//transating position
	Vector3D operator*(const Vector3D vector) const;
	static Matrix2DE translate(float x, float y);
	static Matrix2DE translate(const Vector3D& position);

	//rotating around an angle
	static Matrix2DE rotateZ(float angleinRadians);

	//matrix * matrix multiplcation
	Matrix2DE operator*(const Matrix2DE otherMatrix);

	static Matrix2DE scale(float x, float y);

	

};






#endif