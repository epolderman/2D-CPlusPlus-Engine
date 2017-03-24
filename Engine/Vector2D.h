#ifndef ENGINE_VECTOR_2D_H
#define ENGINE_VECTOR_2D_H

namespace math
{

	struct Vector2D
	{
		Vector2D(float x = 0.0f, float y = 0.0f) : x(x), y(y)
		{

		}
		float x;
		float y;


	};

	Vector2D operator+(const Vector2D& left, const Vector2D& right)
	{		
		return Vector2D(left.x + right.x, left.y + right.y);
	}

}



#endif