#ifndef GUMIGOTA_LOG_H
#define GUMIGOTA_LOG_H



/* INCLUDES */
// Normal Includes
#include <iostream>



#ifndef NDEBUG

	#define LOG(x) std::cout << "[GumiGota] " << x << std::endl

#else

	#define LOG(x)

#endif /* NDEBUG */



#endif