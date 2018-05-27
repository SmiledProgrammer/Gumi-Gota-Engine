
/* INCLUDES */
// Self Include
#include "OpenGLHelpFunctions.h"



namespace gg
{

	/* FUNCTIONS */
	void translateToGLCoordinates(vector2& screenCoords, const Window& window)
	{
		float width = (float)window.getWidth();
		float height = (float)window.getHeight();

		screenCoords.x = (2.0f * screenCoords.x) / width - 1.0f;
		screenCoords.y = (2.0f * screenCoords.y) / height - 1.0f;
	}

}