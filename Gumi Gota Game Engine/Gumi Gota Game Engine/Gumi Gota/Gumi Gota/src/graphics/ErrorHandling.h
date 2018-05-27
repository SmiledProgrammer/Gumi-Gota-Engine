#ifndef GUMIGOTA_ERROR_HANDLING_H
#define GUMIGOTA_ERROR_HANDLING_H



/* DEFINITIONS */
#ifndef NDEBUG

	#define ASSERT(x) if (!(x)) __debugbreak();
	#define GLcall(x) GLclearError();\
		x;\
		ASSERT(GLlogCall(#x, __FILE__, __LINE__))

#else

	#define ASSERT(x) x
	#define GLcall(x) x

#endif /* NDEBUG */


namespace gg
{

	/* Functions */
	void GLclearError();

	bool GLlogCall(const char* function, const char* file, const int line);

}



#endif