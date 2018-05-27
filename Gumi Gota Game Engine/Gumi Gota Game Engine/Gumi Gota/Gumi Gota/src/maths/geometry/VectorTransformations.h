#ifndef GUMIGOTA_VECTORTRANSFORMATIONS_H
#define GUMIGOTA_VECTORTRANSFORMATIONS_H



/* INCLUDES */
// Header Includes
#include "../vectors/vector2.h"
#include "../vectors/vector3.h"
#include "../vectors/vector4.h"



namespace gg
{

	/* FUNCTIONS */
	float dotProduct(const vector2& v1, const vector2& v2);
	float dotProduct(const vector3& v1, const vector3& v2);
	float dotProduct(const vector4& v1, const vector4& v2);

	vector3 crossProduct(const vector3& v1, const vector3& v2);
	vector4 crossProduct(const vector4& v1, const vector4& v2);

	vector3 normal(const vector3& vec);
	vector4 normal(const vector4& vec);

}



#endif