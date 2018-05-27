#ifndef GUMIGOTA_BASICOPERATIONS_H
#define GUMIGOTA_BASICOPERATIONS_H



/* INCLUDES */
// Normal Includes
#include <vector>



namespace gg
{

	/* FUNCTIONS */
	float power(const float base, const float exponent);
	float squareRoot(const float number);

	float absolute(const float number);

	float maximum(const float v0, const float v1);
	float minimum(const float v0, const float v1);

	float clamp(const float value, const float min, const float max);


	std::vector<float> lowestValues(const std::vector<float>& numbers, const unsigned int amount);
	std::vector<int> lowestIndices(const std::vector<float>& numbers, const unsigned int amount);

}



#endif