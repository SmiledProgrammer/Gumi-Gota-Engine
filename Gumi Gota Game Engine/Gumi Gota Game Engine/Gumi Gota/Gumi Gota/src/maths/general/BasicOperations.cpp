
/* INCLUDES */
// Self Include
#include "BasicOperations.h"

// Normal Includes
#include <cmath>

#include <iostream> ///remove l8r



namespace gg
{

	/* FUNCTIONS */
	float power(const float base, const float exponent)
	{
		return pow(base, exponent);
	}

	float squareRoot(const float number)
	{
		return power(number, 0.5f);
	}


	float absolute(const float number)
	{
		return (number >= 0.0f) ? number : -number;
	}


	float maximum(const float v0, const float v1)
	{
		return (v0 > v1) ? v0 : v1;
	}

	float minimum(const float v0, const float v1)
	{
		return (v0 < v1) ? v0 : v1;
	}


	float clamp(const float value, const float min, const float max)
	{
		return (value < max) ? ((value > min) ? value : min) : max;
	}



	std::vector<float> lowestValues(const std::vector<float>& numbers, const unsigned int amount)
	{
		// Init
		std::vector<float> lowestValues;
		std::vector<int> lowestIndices;

		lowestValues.reserve(amount);
		lowestIndices.reserve(amount);

		for (unsigned int i = 0; i < amount; i++)
		{
			lowestValues.push_back(100000000.0f);
			lowestIndices.push_back(-1);
		}

		// Finding Lowest Values
		for (unsigned int i = 0; i < numbers.size(); i++)
		{
			for (unsigned int j = 0; j < amount; j++)
			{
				if (numbers[i] < lowestValues[j])
				{
					lowestValues.erase(lowestValues.end() - 1);
					lowestIndices.erase(lowestIndices.end() - 1);

					lowestValues.insert(lowestValues.begin() + j, numbers[i]);
					lowestIndices.insert(lowestIndices.begin() + j, i);

					j = amount;
				}
			}
		}


		return lowestValues;
	}

	std::vector<int> lowestIndices(const std::vector<float>& numbers, const unsigned int amount)
	{
		// Init
		std::vector<float> lowestValues;
		std::vector<int> lowestIndices;

		lowestValues.reserve(amount);
		lowestIndices.reserve(amount);

		for (unsigned int i = 0; i < amount; i++)
		{
			lowestValues.push_back(100000000.0f);
			lowestIndices.push_back(-1);
		}

		// Finding Lowest Values
		for (unsigned int i = 0; i < numbers.size(); i++)
		{
			for (unsigned int j = 0; j < amount; j++)
			{
				if (numbers[i] < lowestValues[j])
				{
					lowestValues.erase(lowestValues.end() - 1);
					lowestIndices.erase(lowestIndices.end() - 1);

					lowestValues.insert(lowestValues.begin() + j, numbers[i]);
					lowestIndices.insert(lowestIndices.begin() + j, i);

					j = amount;
				}
			}
		}


		return lowestIndices;
	}

}