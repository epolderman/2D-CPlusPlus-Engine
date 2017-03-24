#include "Vector3D.h"


void Vector3D::setX(float xx)
{
	x = xx;
}
void Vector3D::setY(float yy)
{
	y = yy;
}
void Vector3D::setZ(float zz)
{
	z = zz;
}
float Vector3D::getX() const
{
	return x;
}
float Vector3D::getY() const
{
	return y;
}
float Vector3D::getZ() const
{
	return z;
}
//scalar
Vector3D Vector3D::operator*(float scalar) const
{
	return Vector3D(scalar * x, scalar * y, scalar * z);
}
//+=
//NOTES//
//+= is faster than +(down below) because...
Vector3D& Vector3D::operator+=(const Vector3D& otherVector)
{
	///...we are shoving the Othervector.getX() coming in into this-x object
	///...we are not creating a new temp object

	this->x += otherVector.getX();
	this->y += otherVector.getY();
	this->z += otherVector.getZ();
	return *this; //<---always returns a reference to the newly alatered left hand side (enables operator chaining a = b = c)
}
//Vector Addition (+)
Vector3D Vector3D::operator+(const Vector3D& otherVector)
{
	//has to create a temporary object on the stack frame thus making it slower
	return Vector3D(x + otherVector.getX(), y + otherVector.getY(), z + otherVector.getZ()); ///<-- return value optimzation
}
//vector subtraction (-)
Vector3D Vector3D::operator-(const Vector3D& otherVector)
{
	return(Vector3D(x - otherVector.getX(),
					y - otherVector.getY(), 
					z - otherVector.getZ())); 
}
//to the right
Vector3D Vector3D::ClockWisePerpindicular() const
{
	return(Vector3D(y, -x, z));
}
//to the left
Vector3D Vector3D::CounterClockWisePerp() const
{
	return(Vector3D(-y, x, z));
}


///HIGHLY FUCKING IMPORTANT///
//Dot Product Breakdown
// a dot b = |a||b|cos(theta)
//think of the dot product as a projection of one vector onto the other
//to project a onto b then normalize |b| so the resulting line of code would be
// a dot b.normalize(); -> which gives you the length of the vector(magnitude) a
//projected onto b. then scale b by the product of the dot operation to get that resulting
//vector shadow of a onto b.
//Remember if you want a vectors direction flipped (multiply it by -1)
///
float Vector3D::Dot(const Vector3D& othervector) const
{
	return(this->getX() * othervector.getX() +
			this->getY() * othervector.getY() +
			this->getZ() * othervector.getZ());
}

//the magnitude (requires expensive square root call)
float Vector3D::Length() const
{
	return sqrt(magnitudeSquared());
}

//optmized to not call length 3 times for each vector value(x, y , z)
Vector3D Vector3D::Normalize()
{
	const float inverseMagnitude = 1.0f / Length();
	//return Vector3D(x / Length() , y / Length() , z / Length());
	return (*this) * inverseMagnitude;
}

//determines the length of a vector(when comparing vectors length)
//optmization we dont have to call the EXPENSIVE sqrt
float Vector3D::magnitudeSquared() const
{
	//optmization this vector dot product against itself
	//cos theta in the dot product = 0 (so cost(theta) = 1)
	//(*this) access this vector and pass the underlying data through
	return this->Dot(*this);
}

//projecting one vector onto the other without using the expensive sqrt(27x
//more expensive than a + operator)
// (direction of b(other)) * a dot b / |b|magnitudesquared();
Vector3D Vector3D::projectOnto(const Vector3D& other) const
{
	return other * (this->Dot(other) / other.magnitudeSquared());
}

///LERP LINEAR INTERPOLATION
//Uses are pathtracing, sending a player, ship to move along a vectorized path
//Takes two vectors multiplied by a float value(alpha) so we can increment
//along the vector that connects a + b = c (so along c).
//creates a vectorized triangle in the original vector becaus you are using
//vectorized addition on the scaling the original a and b so it creates another
//vector POINTING at the linear interpolation value along C. 

Vector3D Vector3D::lerp(float alpha, const Vector3D& b) const
{
	float value = 1.0f - alpha;
	return Vector3D((*this) * value + (b * alpha));
}
