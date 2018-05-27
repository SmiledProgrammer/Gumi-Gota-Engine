
/* INCLUDES */
// Self Include
#include "Sorting.h"



namespace gg
{

	/* ADDITIONAL STUFF */
	// Swap Functions
	static void s_swap(float* values, const int index1, const int index2)
	{
		float copy = values[index1];
		values[index1] = values[index2];
		values[index2] = copy;
	}

	static void s_swap(std::vector<float>& values, const int index1, const int index2)
	{
		float copy = values[index1];
		values[index1] = values[index2];
		values[index2] = copy;
	}

	static void s_swap(std::vector<unsigned int>& indices, const int index1, const int index2)
	{
		unsigned int copy = indices[index1];
		indices[index1] = indices[index2];
		indices[index2] = copy;
	}

	// Quick Sort
	static void s_quickSortValues(float* values, const int startIndex, const int endIndex)
	{
		if (startIndex < endIndex)
		{
			float pivot = values[endIndex];
			int partitionIndex = startIndex;

			for (unsigned int i = startIndex; i < endIndex; i++)
			{
				if (values[i] <= pivot)
				{
					s_swap(values, i, partitionIndex);
					partitionIndex++;
				}
			}

			s_swap(values, endIndex, partitionIndex);

			s_quickSortValues(values, startIndex, partitionIndex - 1);
			s_quickSortValues(values, partitionIndex + 1, endIndex);
		}
	}

	static void s_quickSortValues(std::vector<float>& values, const int startIndex, const int endIndex)
	{
		if (startIndex < endIndex)
		{
			float pivot = values[endIndex];
			int partitionIndex = startIndex;

			for (unsigned int i = startIndex; i < endIndex; i++)
			{
				if (values[i] <= pivot)
				{
					s_swap(values, i, partitionIndex);
					partitionIndex++;
				}
			}

			s_swap(values, endIndex, partitionIndex);

			s_quickSortValues(values, startIndex, partitionIndex - 1);
			s_quickSortValues(values, partitionIndex + 1, endIndex);
		}
	}


	static void s_quickSortIndicesValuesFromArray(std::vector<unsigned int>& indices, float* values, const int startIndex, const int endIndex)
	{
		if (startIndex < endIndex)
		{
			float pivot = values[endIndex];
			int partitionIndex = startIndex;

			for (unsigned int i = startIndex; i < endIndex; i++)
			{
				if (values[i] <= pivot)
				{
					s_swap(values, i, partitionIndex);
					s_swap(indices, i, partitionIndex);
					partitionIndex++;
				}
			}

			s_swap(values, endIndex, partitionIndex);
			s_swap(indices, endIndex, partitionIndex);

			s_quickSortIndicesValuesFromArray(indices, values, startIndex, partitionIndex - 1);
			s_quickSortIndicesValuesFromArray(indices, values, partitionIndex + 1, endIndex);
		}
	}

	static void s_quickSortIndicesValuesFromVector(std::vector<unsigned int>& indices, std::vector<float>& values, const int startIndex, const int endIndex)
	{
		if (startIndex < endIndex)
		{
			float pivot = values[endIndex];
			int partitionIndex = startIndex;

			for (unsigned int i = startIndex; i < endIndex; i++)
			{
				if (values[i] <= pivot)
				{
					s_swap(values, i, partitionIndex);
					s_swap(indices, i, partitionIndex);
					partitionIndex++;
				}
			}

			s_swap(values, endIndex, partitionIndex);
			s_swap(indices, endIndex, partitionIndex);

			s_quickSortIndicesValuesFromVector(indices, values, startIndex, partitionIndex - 1);
			s_quickSortIndicesValuesFromVector(indices, values, partitionIndex + 1, endIndex);
		}
	}



	/* FUNCTIONS */
	// Quick Sort
	void quickSortValues(float* values, const unsigned int size)
	{
		// Init
		unsigned int startIndex = 0;
		unsigned int endIndex = size - 1;

		// Sorting
		if (startIndex < endIndex)
		{
			float pivot = values[endIndex];
			int partitionIndex = startIndex;

			for (unsigned int i = startIndex; i < endIndex; i++)
			{
				if (values[i] <= pivot)
				{
					s_swap(values, i, partitionIndex);
					partitionIndex++;
				}
			}

			s_swap(values, endIndex, partitionIndex);

			s_quickSortValues(values, startIndex, partitionIndex - 1);
			s_quickSortValues(values, partitionIndex + 1, endIndex);
		}
	}

	void quickSortValues(std::vector<float>& values)
	{
		// Init
		unsigned int startIndex = 0;
		unsigned int endIndex = values.size() - 1;

		// Sorting
		if (startIndex < endIndex)
		{
			float pivot = values[endIndex];
			int partitionIndex = startIndex;

			for (unsigned int i = startIndex; i < endIndex; i++)
			{
				if (values[i] <= pivot)
				{
					s_swap(values, i, partitionIndex);
					partitionIndex++;
				}
			}

			s_swap(values, endIndex, partitionIndex);

			s_quickSortValues(values, startIndex, partitionIndex - 1);
			s_quickSortValues(values, partitionIndex + 1, endIndex);
		}
	}


	std::vector<unsigned int> quickSortIndices(float* values, const unsigned int size)
	{
		// Init
		unsigned int startIndex = 0;
		unsigned int endIndex = size - 1;

		std::vector<unsigned int> result;
		result.reserve(endIndex);
		for (unsigned int i = 0; i < endIndex; i++)
		{
			result.push_back(i);
		}

		// Sorting
		if (startIndex < endIndex)
		{
			float pivot = values[endIndex];
			int partitionIndex = startIndex;

			for (unsigned int i = startIndex; i < endIndex; i++)
			{
				if (values[i] <= pivot)
				{
					s_swap(values, i, partitionIndex);
					s_swap(result, i, partitionIndex);
					partitionIndex++;
				}
			}

			s_swap(values, endIndex, partitionIndex);
			s_swap(result, endIndex, partitionIndex);

			s_quickSortIndicesValuesFromArray(result, values, startIndex, partitionIndex - 1);
			s_quickSortIndicesValuesFromArray(result, values, partitionIndex + 1, endIndex);
		}


		return result;
	}

	std::vector<unsigned int> quickSortIndices(std::vector<float>& values)
	{
		// Init
		unsigned int startIndex = 0;
		unsigned int endIndex = values.size() - 1;

		std::vector<unsigned int> result;
		result.reserve(endIndex);
		for (unsigned int i = 0; i < endIndex + 1; i++)
		{
			result.push_back(i);
		}

		// Sorting
		if (startIndex < endIndex)
		{
			float pivot = values[endIndex];
			int partitionIndex = startIndex;

			for (unsigned int i = startIndex; i < endIndex; i++)
			{
				if (values[i] <= pivot)
				{
					s_swap(values, i, partitionIndex);
					s_swap(result, i, partitionIndex);
					partitionIndex++;
				}
			}

			s_swap(values, endIndex, partitionIndex);
			s_swap(result, endIndex, partitionIndex);

			s_quickSortIndicesValuesFromVector(result, values, startIndex, partitionIndex - 1);
			s_quickSortIndicesValuesFromVector(result, values, partitionIndex + 1, endIndex);
		}


		return result;
	}

	// Insert Sort
	void insertSortValues(float* values, const unsigned int size)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			int partitionIndex = 0;

			for (unsigned int j = i; j > 0; j--)
			{
				if (values[i - partitionIndex] < values[j - 1])
				{
					s_swap(values, i - partitionIndex, j - 1);
					partitionIndex++;
				}
			}
		}
	}

	void insertSortValues(std::vector<float>& values)
	{
		for (unsigned int i = 0; i < values.size(); i++)
		{
			int partitionIndex = 0;

			for (unsigned int j = i; j > 0; j--)
			{
				if (values[i - partitionIndex] < values[j - 1])
				{
					s_swap(values, i - partitionIndex, j - 1);
					partitionIndex++;
				}
			}
		}
	}


	std::vector<unsigned int> insertSortIndices(float* values, const unsigned int size)
	{
		// Init
		unsigned int endIndex = size - 1;

		std::vector<unsigned int> result;
		result.reserve(endIndex);
		for (unsigned int i = 0; i < endIndex + 1; i++)
		{
			result.push_back(i);
		}

		// Sorting
		for (unsigned int i = 0; i < size; i++)
		{
			int partitionIndex = 0;

			for (unsigned int j = i; j > 0; j--)
			{
				if (values[i - partitionIndex] < values[j - 1])
				{
					s_swap(values, i - partitionIndex, j - 1);
					s_swap(result, i - partitionIndex, j - 1);
					partitionIndex++;
				}
			}
		}


		return result;
	}

	std::vector<unsigned int> insertSortIndices(std::vector<float>& values)
	{
		// Init
		unsigned int endIndex = values.size() - 1;

		std::vector<unsigned int> result;
		result.reserve(endIndex);
		for (unsigned int i = 0; i < endIndex + 1; i++)
		{
			result.push_back(i);
		}

		// Sorting
		for (unsigned int i = 0; i < values.size(); i++)
		{
			int partitionIndex = 0;

			for (unsigned int j = i; j > 0; j--)
			{
				if (values[i - partitionIndex] < values[j - 1])
				{
					s_swap(values, i - partitionIndex, j - 1);
					s_swap(result, i - partitionIndex, j - 1);
					partitionIndex++;
				}
			}
		}


		return result;
	}

}