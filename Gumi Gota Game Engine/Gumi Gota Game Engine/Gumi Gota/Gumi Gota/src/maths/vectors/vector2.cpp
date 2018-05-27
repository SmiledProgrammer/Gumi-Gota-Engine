
/* INCLUDES */
// Self Include
#include "vector2.h"

// Header Includes
#include "../general/BasicOperations.h"



namespace gg
{

	/* ADDITIONAL FUNCTIONS */
	static float abs(const float value)
	{
		return value < 0.0f ? -value : value;
	}



	/* Constructors */
	vector2::vector2()
		: x(0.0f), y(0.0f)
	{}

	vector2::vector2(const float value)
		: x(value), y(value)
	{}

	vector2::vector2(const float x, const float y)
		: x(x), y(y)
	{}

	/* Functions */
	vector2& vector2::add(const vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	vector2& vector2::subtract(const vector2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	vector2& vector2::multiply(const vector2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	vector2& vector2::divide(const vector2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}


	vector2 vector2::opposite() const
	{
		return vector2(-x, -y);
	}


	vector2 vector2::absolute() const
	{
		return vector2(abs(x), abs(y));
	}


	float vector2::length()
	{
		return squareRoot(x * x + y * y);
	}

	float vector2::lengthSquared()
	{
		return x * x + y * y;
	}

	/* Operator Overloads */
	vector2 operator+(vector2 left, const vector2& right)
	{
		return left.add(right);
	}

	vector2 operator-(vector2 left, const vector2& right)
	{
		return left.subtract(right);
	}

	vector2 operator*(vector2 left, const vector2& right)
	{
		return left.multiply(right);
	}

	vector2 operator/(vector2 left, const vector2& right)
	{
		return left.divide(right);
	}


	vector2& vector2::operator+=(const vector2& other)
	{
		return add(other);
	}

	vector2& vector2::operator-=(const vector2& other)
	{
		return subtract(other);
	}

	vector2& vector2::operator*=(const vector2& other)
	{
		return multiply(other);
	}

	vector2& vector2::operator/=(const vector2& other)
	{
		return divide(other);
	}


	vector2 operator*(vector2 vec, const float value)
	{
		return vector2(vec.x * value, vec.y * value);
	}

	vector2 operator/(vector2 vec, const float value)
	{
		return vector2(vec.x / value, vec.y / value);
	}


	vector2& vector2::operator*=(const float value)
	{
		x *= value;
		y *= value;

		return *this;
	}

	vector2& vector2::operator/=(const float value)
	{
		x /= value;
		y /= value;

		return *this;
	}



	bool vector2::operator==(const vector2& other) const
	{
		return x == other.x && y == other.y;
	}

	bool vector2::operator!=(const vector2& other) const
	{
		return !(*this == other);
	}

}