
/* INCLUDES */
// Self Include
#include "Timer.h"

// OpenGL Includes
#include <GLFW/glfw3.h>

// Header Includes
#include "../graphics/ErrorHandling.h"



namespace gg
{

	/* Constructors */
	Timer::Timer()
	{
		GLcall(m_startTime = glfwGetTime());
	}

	/* Functions */
	void Timer::reset()
	{
		GLcall(m_startTime = glfwGetTime());
	}


	float Timer::elapsed() const
	{
		GLcall(return (float)(glfwGetTime() - m_startTime));
	}

}