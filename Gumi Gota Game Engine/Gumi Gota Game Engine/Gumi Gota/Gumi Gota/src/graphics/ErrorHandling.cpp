
/* INCLUDES */
// Self Include
#include "ErrorHandling.h"

// OpenGL Includes
#include "GL/glew.h"

// Header Includes
#include "../Log.h"



namespace gg
{

	/* Functions */
	void GLclearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}


	bool GLlogCall(const char* function, const char* file, const int line)
	{
		while (GLenum error = glGetError())
		{
			LOG("[Error] (" << error << "): " << function << " " << file << ":" << line);

			return false;
}

		return true;
	}

}