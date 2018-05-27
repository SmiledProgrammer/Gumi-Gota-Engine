#ifndef GUMIGOTA_WINDOW_H
#define GUMIGOTA_WINDOW_H



/* INCLUDES */
// OpenGL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Header Includes
#include "../maths/vectors/vector2.h"
#include "../maths/vectors/vector4.h"

#include "Color.h"



/* CONSTANTS */
#define MAX_KEYS 1024
#define MAX_BUTTONS 32



namespace gg
{

	class Window
	{
	private:
		/* Variables */
		const char* m_title;
		int m_width, m_height;
		bool m_closed;
		GLFWwindow* m_window;

		bool m_keys[MAX_KEYS]; //used for checking if keyboard keys are pressed
		bool m_buttons[MAX_BUTTONS]; //used for checking if mouse buttons are pressed
		vector2 m_mousePos; //used for storing information about mouse position

	public:
		/* Constructors */
		Window(const char* title, const unsigned int& width, const unsigned int& height);

		/* Destructor */
		~Window();

		/* Functions */
		void update();
		void clear() const;

		void setClearColor(const Color& color) const;
		void setMousePosition(vector2 pos);
		void setMouseToCenter();

		void hideCursor();
		void showCursor();

		void close();

		bool closed() const;

		// Getters
		float getAspectRatio() const;

		inline int     getWidth()  const { return m_width;  }
		inline int     getHeight() const { return m_height; }
		inline vector2 getSize()   const { return vector2((float)m_width, (float)m_height); }

		bool isKeyPressed(unsigned int key) const;
		bool isButtonPressed(unsigned int button) const;
		vector2 getMousePosition() const;

		bool isOnTop() const;

	private:
		// Private Functions
		bool m_init();

		/* Additional Functions */
		friend static void windowResize(GLFWwindow* window, int width, int height);

		friend static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void buttonCallback(GLFWwindow* window, int button, int action, int mods);
		friend static void mousePositionCallback(GLFWwindow* window, double xPos, double yPos);

	};

}



#endif