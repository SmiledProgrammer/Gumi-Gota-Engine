
/* INCLUDES */
// Self Include
#include "AngleTransformations.h"

// Header Includes
#include "../general/Constants.h"



namespace gg
{

	/* OPERATIONS */
	float toRadians(const float degrees)
	{
		return degrees * PI / 180.0f;
	}

	float toDegrees(const float radians)
	{
		return radians * 180.0f / PI;
	}

}