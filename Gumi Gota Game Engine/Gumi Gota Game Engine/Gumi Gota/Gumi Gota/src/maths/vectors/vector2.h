#ifndef GUMIGOTA_VECTOR2_H
#define GUMIGOTA_VECTOR2_H



namespace gg
{

	struct vector2
	{
		/* Variables */
		float x, y;

		/* Constructors */
		vector2();
		vector2(const float value);
		vector2(const float x, const float y);

		/* Functions */
		vector2& add(const vector2& other);
		vector2& subtract(const vector2& other);
		vector2& multiply(const vector2& other);
		vector2& divide(const vector2& other);

		vector2 opposite() const;

		vector2 absolute() const;

		float length();
		float lengthSquared();

		/* Operator Overloads */
		friend vector2 operator+(vector2 left, const vector2& right);
		friend vector2 operator-(vector2 left, const vector2& right);
		friend vector2 operator*(vector2 left, const vector2& right);
		friend vector2 operator/(vector2 left, const vector2& right);

		vector2& operator+=(const vector2& other);
		vector2& operator-=(const vector2& other);
		vector2& operator*=(const vector2& other);
		vector2& operator/=(const vector2& other);

		friend vector2 operator*(vector2 vec, const float value);
		friend vector2 operator/(vector2 vec, const float value);

		vector2& operator*=(const float value);
		vector2& operator/=(const float value);


		bool operator==(const vector2& other) const;
		bool operator!=(const vector2& other) const;

	};

}



#endif