
/* INCLUDES */
// Self Include
#include "Window.h"

// Normal Includes
#include <stdlib.h>
#include <time.h>

// Header Includes
#include "ErrorHandling.h"

#include "../Log.h"



namespace gg
{

	/* Constructors */
	Window::Window(const char* title, const unsigned int& width, const unsigned int& height)
		: m_title(title), m_width(width), m_height(height)
	{
		if (!m_init())
			glfwTerminate();

		// Input Init
		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_keys[i] = false;
		}

		for (int i = 0; i < MAX_BUTTONS; i++)
		{
			m_buttons[i] = false;
		}
	}

	/* Destructor */
	Window::~Window()
	{
		glfwTerminate();
	}

	/* Functions */
	void Window::update()
	{
		// Swapping Buffers
		GLcall(glfwSwapBuffers(m_window));

		// Event Handling
		GLcall(glfwPollEvents());
	}

	void Window::clear() const
	{
		GLcall( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) );
	}


	void Window::setClearColor(const Color& color) const
	{
		GLcall(glClearColor(color.r, color.g, color.b, color.a));
	}

	void Window::setMousePosition(vector2 pos)
	{
		GLcall(glfwSetCursorPos(m_window, (double)pos.x, (double)pos.y));
	}

	void Window::setMouseToCenter()
	{
		GLcall(glfwSetCursorPos(m_window, (double)(m_width / 2), (double)(m_height / 2)));
	}


	void Window::hideCursor()
	{
		GLcall(glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN));
	}

	void Window::showCursor()
	{
		GLcall(glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL));
	}


	void Window::close()
	{
		GLcall(glfwSetWindowShouldClose(m_window, 1));
	}


	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_window) == 1;
	}

	// Getters
	float Window::getAspectRatio() const
	{
		return (float)m_width / (float)m_height;
	}


	bool Window::isKeyPressed(unsigned int key) const
	{
		if (key >= MAX_KEYS)
			return false;

		return m_keys[key];
	}

	bool Window::isButtonPressed(unsigned int button) const
	{
		if (button >= MAX_BUTTONS)
			return false;

		return m_buttons[button];
	}

	vector2 Window::getMousePosition() const
	{
		return m_mousePos;
	}


	bool Window::isOnTop() const
	{
		if (m_window == glfwGetCurrentContext())
			return true;

		return false;
	}

	// Private Functions
	bool Window::m_init()
	{
		// C Stuff
		srand((unsigned int)time(NULL));

		// Initializing GLFW
		if (!glfwInit())
		{
			LOG("[Error] GLFW couldn't initialize!");

			return false;
		}

		// Creating Window
		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

		// Checking for Window Opening Fail
		if (!m_window)
		{
			LOG("[Error] Failed to create GLFW window!");

			return false;
		}

		// Making Context Current
		glfwMakeContextCurrent(m_window);

		glfwSetWindowUserPointer(m_window, this);

		// Resize Handling
		glfwSetFramebufferSizeCallback(m_window, windowResize);

		// Input Handling
		glfwSetKeyCallback(m_window, keyCallback);
		glfwSetMouseButtonCallback(m_window, buttonCallback);
		glfwSetCursorPosCallback(m_window, mousePositionCallback);


		// Initializing GLEW
		if (glewInit() != GLEW_OK)
		{
			LOG("[Error] GLEW couldn't initialize!");

			return false;
		}

		// Version Setting
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Optimization Stuff
		GLcall(glfwSwapInterval(0)); //turning off v-sync


		return true;
	}


	/* Additional Functions */
	void windowResize(GLFWwindow* window, int width, int height)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window); //getting the window class

		// Resizing Stuff
		GLcall(glViewport(0, 0, width, height));

		// Updating Window Class Variables
		win->m_width = width;
		win->m_height = height;
	}


	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window); //getting the window class

		win->m_keys[key] = (action != GLFW_RELEASE);
	}

	void buttonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window); //getting the window class

		win->m_buttons[button] = (action != GLFW_RELEASE);
	}

	void mousePositionCallback(GLFWwindow* window, double xPos, double yPos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window); //getting the window class

		win->m_mousePos = vector2((float)xPos, (float)yPos);
	}

}