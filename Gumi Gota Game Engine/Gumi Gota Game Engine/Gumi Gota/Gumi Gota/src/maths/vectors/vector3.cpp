
/* INCLUDES */
// Self Include
#include "vector3.h"

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
	vector3::vector3()
		: x(0.0f), y(0.0f), z(0.0f)
	{}

	vector3::vector3(const float value)
		: x(value), y(value), z(value)
	{}

	vector3::vector3(const vector2& xy, const float z)
		: x(xy.x), y(xy.y), z(z)
	{}

	vector3::vector3(const float x, const float y, const float z)
		: x(x), y(y), z(z)
	{}

	/* Functions */
	vector3& vector3::add(const vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	vector3& vector3::subtract(const vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	vector3& vector3::multiply(const vector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	vector3& vector3::divide(const vector3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}


	vector3 vector3::opposite() const
	{
		return vector3(-x, -y, -z);
	}


	vector3 vector3::absolute() const
	{
		return vector3(abs(x), abs(y), abs(y));
	}


	vector2 vector3::xy()
	{
		return vector2(x, y);
	}


	float vector3::length()
	{
		return squareRoot(x * x + y * y + z * z);
	}

	float vector3::lengthSquared()
	{
		return x * x + y * y + z * z;
	}


	void vector3::normalize()
	{
		float magnitude = length();

		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}

	/* Operator Overloads */
	vector3 operator+(vector3 left, const vector3& right)
	{
		return left.add(right);
	}

	vector3 operator-(vector3 left, const vector3& right)
	{
		return left.subtract(right);
	}

	vector3 operator*(vector3 left, const vector3& right)
	{
		return left.multiply(right);
	}

	vector3 operator/(vector3 left, const vector3& right)
	{
		return left.divide(right);
	}


	vector3& vector3::operator+=(const vector3& other)
	{
		return add(other);
	}

	vector3& vector3::operator-=(const vector3& other)
	{
		return subtract(other);
	}

	vector3& vector3::operator*=(const vector3& other)
	{
		return multiply(other);
	}

	vector3& vector3::operator/=(const vector3& other)
	{
		return divide(other);
	}


	vector3 operator*(vector3 vec, const float value)
	{
		return vector3(vec.x * value, vec.y * value, vec.z * value);
	}

	vector3 operator/(vector3 vec, const float value)
	{
		return vector3(vec.x / value, vec.y / value, vec.z / value);
	}


	vector3& vector3::operator*=(const float value)
	{
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	vector3& vector3::operator/=(const float value)
	{
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}



	bool vector3::operator==(const vector3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool vector3::operator!=(const vector3& other) const
	{
		return !(*this == other);
	}

}