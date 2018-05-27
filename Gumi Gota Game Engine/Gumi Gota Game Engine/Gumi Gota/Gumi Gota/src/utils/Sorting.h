#ifndef GUMIGOTA_SORTING_H
#define GUMIGOTA_SORTING_H



/* INCLUDES */
// Normal Includes
#include <vector>



namespace gg
{

	/* FUNCTIONS */
	// Quick Sort
	void quickSortValues(float* values, const unsigned int size);
	void quickSortValues(std::vector<float>& values);
	
	std::vector<unsigned int> quickSortIndices(float* values, const unsigned int size); //sorts values and returns indices (new order) of values
	std::vector<unsigned int> quickSortIndices(std::vector<float>& values); //sorts values and returns indices (new order) of values

	// Insert Sort
	void insertSortValues(float* values, const unsigned int size);
	void insertSortValues(std::vector<float>& values);

	std::vector<unsigned int> insertSortIndices(float* values, const unsigned int size);
	std::vector<unsigned int> insertSortIndices(std::vector<float>& values);

}



#endif