
/* INCLUDES */
// Self Include
#include "VectorTransformations.h"

// Header Includes
#include "../general/BasicOperations.h"

#include "../trigonometry/Trigonometry.h"



namespace gg
{

	/* FUNCTIONS */
	float dotProduct(const vector2& v1, const vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	float dotProduct(const vector3& v1, const vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	float dotProduct(const vector4& v1, const vector4& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}


	vector3 crossProduct(const vector3& v1, const vector3& v2)
	{
		return vector3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);
	}

	vector4 crossProduct(const vector4& v1, const vector4& v2)
	{
		return vector4(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x,
			v1.w
		);
	}
	

	vector3 normal(const vector3& vec)
	{
		float magnitude = squareRoot(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

		return vector3(
			vec.x / magnitude,
			vec.y / magnitude,
			vec.z / magnitude
		);
	}

	vector4 normal(const vector4& vec)
	{
		float magnitude = squareRoot(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

		return vector4(
			vec.x / magnitude,
			vec.y / magnitude,
			vec.z / magnitude,
			vec.w
		);
	}

}