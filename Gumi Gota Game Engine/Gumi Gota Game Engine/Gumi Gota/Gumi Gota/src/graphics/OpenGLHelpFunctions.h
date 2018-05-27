#ifndef GUMIGOTA_OPENGLHELPFUNCTIONS_H
#define GUMIGOTA_OPENGLHELPFUNCTIONS_H



/* INCLUDES */
// Header Includes
#include "../graphics/Window.h"
#include "../maths/vectors/vector2.h"



namespace gg
{

	/* FUNCTIONS */
	void translateToGLCoordinates(vector2& screenCoords, const Window& window);

}



#endif