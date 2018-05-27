#ifndef GUMIGOTA_VECTOR4_H
#define GUMIGOTA_VECTOR4_H



/* INCLUDES */
// Header Includes
#include "../../maths/vectors/vector3.h"

#include "../../maths/matrices/matrix4.h"



namespace gg
{

	struct vector4
	{
		/* Variables */
		float x, y, z, w;

		/* Constructors */
		vector4();
		vector4(const vector3& xyz, const float w);
		vector4(const float x, const float y, const float z, const float w);

		/* Functions */
		vector4& add(const vector4& other);
		vector4& subtract(const vector4& other);
		vector4& multiply(const vector4& other);
		vector4& divide(const vector4& other);

		vector4 opposite() const;

		vector4 absolute() const;

		vector2 xy();
		vector3 xyz();

		float length();
		float lengthSquared();

		void normalize();

		/* Operator Overloads */
		friend vector4 operator+(vector4 left, const vector4& right);
		friend vector4 operator-(vector4 left, const vector4& right);
		friend vector4 operator*(vector4 left, const vector4& right);
		friend vector4 operator/(vector4 left, const vector4& right);

		vector4& operator+=(const vector4& other);
		vector4& operator-=(const vector4& other);
		vector4& operator*=(const vector4& other);
		vector4& operator/=(const vector4& other);

		friend vector4 operator*(vector4 vec, const float value);
		friend vector4 operator/(vector4 vec, const float value);

		vector4& operator*=(const float value);
		vector4& operator/=(const float value);


		bool operator==(const vector4& other) const;
		bool operator!=(const vector4& other) const;

	};

	/* ADDITIONAL FUNCTIONS */
	vector4 operator*(const vector4& vector, const matrix4& matrix);
	vector4 operator*(const matrix4& matrix, const vector4& vector);

}



#endif