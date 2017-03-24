#ifndef ENGINE_VECTOR_H 
#define ENGINE_VECTOR_H 

//_declspec exports the .lib file so other projects can link to it


class _declspec(dllexport) Vector
{

private:
	float x;
	float y;
public:
	explicit Vector();
	explicit Vector(float xx, float yy);
	Vector(Vector& vect);
	void setX(float xx);
	void setY(float yy);
	float getX() const;
	float getY() const;
	Vector operator+(const Vector& otherVector);
	Vector& operator+=(const Vector& otherVector); //allows v1 + v2 + v3
	Vector& operator-=(const Vector& otherVector);
	Vector operator-(const Vector& otherVector);
	Vector operator*(float scalarAmount);
	float DotProduct(const Vector& otherVector);
	
};




#endif 
