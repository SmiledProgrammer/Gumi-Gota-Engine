
/* INCLUDES */
// Self Include
#include "vector4.h"

// Header Includes
#include "../general/BasicOperations.h"



namespace gg
{

	/* ADDITIONAL FUNCTIONS */
	vector4 operator*(const vector4& vector, const matrix4& matrix)
	{
		return vector4(
			matrix.elements[0 + 0 * 4] * vector.x + matrix.elements[0 + 1 * 4] * vector.y + matrix.elements[0 + 2 * 4] * vector.z + matrix.elements[0 + 3 * 4] * vector.w,
			matrix.elements[1 + 0 * 4] * vector.x + matrix.elements[1 + 1 * 4] * vector.y + matrix.elements[1 + 2 * 4] * vector.z + matrix.elements[1 + 3 * 4] * vector.w,
			matrix.elements[2 + 0 * 4] * vector.x + matrix.elements[2 + 1 * 4] * vector.y + matrix.elements[2 + 2 * 4] * vector.z + matrix.elements[2 + 3 * 4] * vector.w,
			matrix.elements[3 + 0 * 4] * vector.x + matrix.elements[3 + 1 * 4] * vector.y + matrix.elements[3 + 2 * 4] * vector.z + matrix.elements[3 + 3 * 4] * vector.w
		);
	}

	vector4 operator*(const matrix4& matrix, const vector4& vector)
	{
		return vector4(
			vector.x * matrix.elements[0 + 0 * 4] + vector.y * matrix.elements[1 + 0 * 4] + vector.z * matrix.elements[2 + 0 * 4] + vector.w * matrix.elements[3 + 0 * 4],
			vector.x * matrix.elements[0 + 1 * 4] + vector.y * matrix.elements[1 + 1 * 4] + vector.z * matrix.elements[2 + 1 * 4] + vector.w * matrix.elements[3 + 1 * 4],
			vector.x * matrix.elements[0 + 2 * 4] + vector.y * matrix.elements[1 + 2 * 4] + vector.z * matrix.elements[2 + 2 * 4] + vector.w * matrix.elements[3 + 2 * 4],
			vector.x * matrix.elements[0 + 3 * 4] + vector.y * matrix.elements[1 + 3 * 4] + vector.z * matrix.elements[2 + 3 * 4] + vector.w * matrix.elements[3 + 3 * 4]
		);
	}


	static float abs(const float value)
	{
		return value < 0.0f ? -value : value;
	}



	/* Constructors */
	vector4::vector4()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}

	vector4::vector4(const vector3& xyz, const float w)
		: x(xyz.x), y(xyz.y), z(xyz.z), w(w)
	{}

	vector4::vector4(const float x, const float y, const float z, const float w)
		: x(x), y(y), z(z), w(w)
	{}

	/* Functions */
	vector4& vector4::add(const vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	vector4& vector4::subtract(const vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	vector4& vector4::multiply(const vector4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	vector4& vector4::divide(const vector4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}


	vector4 vector4::opposite() const
	{
		return vector4(-x, -y, -z, w);
	}


	vector4 vector4::absolute() const
	{
		return vector4(abs(x), abs(y), abs(y), abs(w));
	}


	vector2 vector4::xy()
	{
		return vector2(x, y);
	}

	vector3 vector4::xyz()
	{
		return vector3(x, y, z);
	}


	float vector4::length()
	{
		return squareRoot(x * x + y * y + z * z);
	}

	float vector4::lengthSquared()
	{
		return x * x + y * y + z * z;
	}


	void vector4::normalize()
	{
		float magnitude = length();

		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}

	/* Operator Overloads */
	vector4 operator+(vector4 left, const vector4& right)
	{
		return left.add(right);
	}
		   
	vector4 operator-(vector4 left, const vector4& right)
	{
		return left.subtract(right);
	}
		   
	vector4 operator*(vector4 left, const vector4& right)
	{
		return left.multiply(right);
	}
		   
	vector4 operator/(vector4 left, const vector4& right)
	{
		return left.divide(right);
	}


	vector4& vector4::operator+=(const vector4& other)
	{
		return add(other);
	}

	vector4& vector4::operator-=(const vector4& other)
	{
		return subtract(other);
	}

	vector4& vector4::operator*=(const vector4& other)
	{
		return multiply(other);
	}

	vector4& vector4::operator/=(const vector4& other)
	{
		return divide(other);
	}


	vector4 operator*(vector4 vec, const float value)
	{
		return vector4(vec.x * value, vec.y * value, vec.z * value, vec.w);
	}

	vector4 operator/(vector4 vec, const float value)
	{
		return vector4(vec.x / value, vec.y / value, vec.z / value, vec.w);
	}


	vector4& vector4::operator*=(const float value)
	{
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	vector4& vector4::operator/=(const float value)
	{
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}



	bool vector4::operator==(const vector4& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool vector4::operator!=(const vector4& other) const
	{
		return !(*this == other);
	}

}