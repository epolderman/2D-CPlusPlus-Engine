#ifndef ENGINE_MATRIX_H
#define ENGINE_MATRIX_H
#include "Vector.h"
#include <cmath>



//float members[4] is the same as float topleft, float topright, etc...
//optimizations tells use that float topleft, topright is faster than float members[4]

//explite before constructor tells us that we dont want any implict conversions from
//float to matrix

//* = binary operator = left hand argument * right hand argument

//matrix rotate is a factory function -> feed it radians pops outs a matrix i can work with

//look into explcity and implicit conversions, operator overloading, free functions, friend functions

class _declspec(dllexport) Matrix
{

		public:
		float topleft; //ro co
		float topright; //ro c1
		float bottomleft; //r1 co
		float bottomright; //r1 c1
		//identity matrix
		explicit Matrix(float tl = 1, float tr = 0, 
						float bl = 0, float br = 1);
		Vector operator*(const Vector& vector);
		static Matrix rotate(float angleinRadians);

};

	





#endif