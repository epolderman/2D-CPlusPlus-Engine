#include "Vector.h"

//constructors
Vector::Vector(float xx, float yy)
{
	this->x = xx;
	this->y = yy;
}
Vector::Vector()
{
	this->x = 0.0;
	this->y = 0.0;
}
//copy constructor
Vector::Vector(Vector& source)
{
	this->x = source.getX();
	this->y = source.getY();

}
//getters
float Vector::getX() const
{
	return x;
}
float Vector::getY() const
{
	return y;
}
//setters
void Vector::setX(float xx)
{
	this->x = xx;
}
void Vector::setY(float yy)
{
	this->y = yy;
}
//addition
Vector Vector::operator+(const Vector& otherVector)
{
	return Vector(this->x + otherVector.getX(), this->y + otherVector.getY() );
}
//+= addition
Vector& Vector::operator+=(const Vector& otherVector)
{
	this->x += otherVector.getX();
	this->y += otherVector.getY();
	return *this;
}
//-= subtraction
Vector& Vector::operator-=(const Vector& otherVector)
{
	this->x -= otherVector.getX();
	this->y -= otherVector.getY();
	return *this;
}
//subtraction
Vector Vector::operator-(const Vector& otherVector)
{
	return Vector(this->x - otherVector.getX(), this->y - otherVector.getY());
}
//scalar multiplcation
Vector Vector::operator*(float scalarAmount)
{
	return(Vector(this->x * scalarAmount, this->y * scalarAmount));
}
//dot product
float Vector::DotProduct(const Vector& otherVector)
{
	return ((this->x * otherVector.getX()) + (this->y * otherVector.getY()));
}


