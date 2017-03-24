#ifndef ENGINE_MATRIX_3D_H
#define ENGINE_MATRIX_3D_H
#include "Vector3D.h"

class _declspec(dllexport) Matrix3D
{

public:

	//row major order

	float r0c0; //top left
	float r0c1; //top mid
	float r0c2; //top right

	float r1c0; //mid left
	float r1c1; //mid mid
	float r1c2; //mid right

	float r2c0; //bottom left
	float r2c1; //bottom mid
	float r2c2; //bottom right

	//constructor
	//identity matrix
	explicit Matrix3D(float r0c0 = 1, float r0c1 = 0, float r0c2 = 0,
					  float r1c0 = 0, float r1c1 = 1, float r1c2 = 0,
				      float r2c0 = 0, float r2c1 = 0, float r2c2 = 1) :
					  r0c0(r0c0), r0c1(r0c1), r0c2(r0c2),
				      r1c0(r1c0), r1c1(r1c1), r1c2(r1c2),
					  r2c0(r2c0), r2c1(r2c1), r2c2(r2c2) {}

	//transating position
	Vector3D operator*(const Vector3D vector);
	static Matrix3D translate(float x, float y);

	//rotating around an angle
	static Matrix3D rotateZ(float angleinRadians);

	//matrix * matrix multiplcation
	Matrix3D operator*(const Matrix3D otherMatrix);

	static Matrix3D scale(float x, float y);
};





#endif