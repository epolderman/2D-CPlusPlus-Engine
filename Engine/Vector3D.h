#ifndef ENGINE_VECTOR3D_H
#define ENGINE_VECTOR3D_H
#include <cmath>


class _declspec(dllexport) Vector3D
{

private:
	float x;
	float y;
	float z;
public:
	
	//default constructor and paramater constructor in 1 line!
	explicit Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f)
					  : x(x), y(y), z(z) {}

	void setX(float xx);
	void setY(float yy);
	void setZ(float zz);
	float getX() const;
	float getY() const;
	float getZ() const;

	Vector3D& operator+=(const Vector3D& vector);
	Vector3D operator-(const Vector3D& otherVector);
	Vector3D operator*(float scalar) const;
	Vector3D operator+(const Vector3D& otherVector);
	Vector3D ClockWisePerpindicular() const;
	Vector3D CounterClockWisePerp() const;
	float Dot(const Vector3D& otherVector) const;
	float Length() const; //magnitude
	Vector3D Normalize();
	float magnitudeSquared() const;
	Vector3D projectOnto(const Vector3D& other) const;
	Vector3D lerp(float alpha, const Vector3D& b) const;

};


#endif