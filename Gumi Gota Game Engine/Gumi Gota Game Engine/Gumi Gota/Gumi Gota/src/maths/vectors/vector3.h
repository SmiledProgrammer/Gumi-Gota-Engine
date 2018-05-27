#ifndef GUMIGOTA_VECTOR3_H
#define GUMIGOTA_VECTOR3_H



/* INCLUDES */
// Header Includes
#include "vector2.h"



namespace gg
{

	struct vector3
	{
		/* Variables */
		float x, y, z;

		/* Constructors */
		vector3();
		vector3(const float value);
		vector3(const vector2& xy, const float z);
		vector3(const float x, const float y, const float z);

		/* Functions */
		vector3& add(const vector3& other);
		vector3& subtract(const vector3& other);
		vector3& multiply(const vector3& other);
		vector3& divide(const vector3& other);

		vector3 opposite() const;

		vector3 absolute() const;

		vector2 xy();

		float length();
		float lengthSquared();

		void normalize();

		/* Operator Overloads */
		friend vector3 operator+(vector3 left, const vector3& right);
		friend vector3 operator-(vector3 left, const vector3& right);
		friend vector3 operator*(vector3 left, const vector3& right);
		friend vector3 operator/(vector3 left, const vector3& right);

		vector3& operator+=(const vector3& other);
		vector3& operator-=(const vector3& other);
		vector3& operator*=(const vector3& other);
		vector3& operator/=(const vector3& other);

		friend vector3 operator*(vector3 vec, const float value);
		friend vector3 operator/(vector3 vec, const float value);

		vector3& operator*=(const float value);
		vector3& operator/=(const float value);


		bool operator==(const vector3& other) const;
		bool operator!=(const vector3& other) const;

	};

}



#endif