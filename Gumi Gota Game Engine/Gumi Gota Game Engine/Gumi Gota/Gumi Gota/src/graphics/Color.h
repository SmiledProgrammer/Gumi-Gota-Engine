#ifndef GUMIGOTA_COLOR_H
#define GUMIGOTA_COLOR_H



/* INCLUDES */
// Header Includes
#include "../maths/vectors/vector3.h"
#include "../maths/vectors/vector4.h"



namespace gg
{

	/* ADDITIONAL STUFF */
	enum ColorPreset
	{
		COLOR_BLACK = 0,
		COLOR_GRAY,
		COLOR_WHITE,
		COLOR_RED,
		COLOR_YELLOW,
		COLOR_ORANGE,
		COLOR_GREEN,
		COLOR_BLUE,
		COLOR_AQUA,
		COLOR_PURPLE
	};



	class Color
	{
	public:
		/* Variables */
		float r, g, b, a; //red, green, blue, alpha

		/* Constructors */
		Color();
		Color(const float r, const float g, const float b);
		Color(const float r, const float g, const float b, const float a);
		Color(const vector3& color);
		Color(const vector4& color);
		Color(ColorPreset color);

		/* Functions */
		// Setters
		void setColor(const Color& color);
		void setColor(const float r, const float g, const float b);
		void setColor(const float r, const float g, const float b, const float a);
		void setColor(const vector3& color);
		void setColor(const vector4& color);
		void setColor(ColorPreset color);

	private:
		// Private Functions
		vector4 m_translatePresetColor(ColorPreset color);

	};

}



#endif