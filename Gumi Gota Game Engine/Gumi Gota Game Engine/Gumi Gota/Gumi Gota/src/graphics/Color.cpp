
/* INCLUDES */
// Self Include
#include "Color.h"



namespace gg
{

	/* Constructors */
	Color::Color()
		: r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{}

	Color::Color(const float r, const float g, const float b)
		: r(r), g(g), b(b), a(1.0f)
	{}

	Color::Color(const float r, const float g, const float b, const float a)
		: r(r), g(g), b(b), a(a)
	{}

	Color::Color(const vector3& color)
		: r(color.x), g(color.y), b(color.z), a(1.0f)
	{}

	Color::Color(const vector4& color)
		: r(color.x), g(color.y), b(color.z), a(color.w)
	{}

	Color::Color(ColorPreset color)
	{
		setColor(color);
	}


	/* Functions */
	// Setters
	void Color::setColor(const Color& color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}

	void Color::setColor(const float r, const float g, const float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		a = 1.0f;
	}

	void Color::setColor(const float r, const float g, const float b, const float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void Color::setColor(const vector3& color)
	{
		r = color.x;
		g = color.y;
		b = color.z;
		a = 1.0f;
	}

	void Color::setColor(const vector4& color)
	{
		r = color.x;
		g = color.y;
		b = color.z;
		a = color.w;
	}

	void Color::setColor(ColorPreset color)
	{
		vector4 translatedColor = m_translatePresetColor(color);

		r = translatedColor.x;
		g = translatedColor.y;
		b = translatedColor.z;
		a = translatedColor.w;
	}

	// Private Functions
	vector4 Color::m_translatePresetColor(ColorPreset color)
	{
		switch (color)
		{

		case COLOR_BLACK:
			return vector4(0.0f, 0.0f, 0.0f, 1.0f);
			break;

		case COLOR_GRAY:
			return vector4(0.5f, 0.5f, 0.5f, 1.0f);
			break;

		case COLOR_WHITE:
			return vector4(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		case COLOR_RED:
			return vector4(1.0f, 0.0f, 0.0f, 1.0f);
			break;

		case COLOR_YELLOW:
			return vector4(1.0f, 1.0f, 0.0f, 1.0f);
			break;

		case COLOR_ORANGE:
			return vector4(1.0f, 0.5f, 0.0f, 1.0f);
			break;

		case COLOR_GREEN:
			return vector4(0.0f, 1.0f, 0.0f, 1.0f);
			break;

		case COLOR_BLUE:
			return vector4(0.0f, 0.0f, 1.0f, 1.0f);
			break;

		case COLOR_AQUA:
			return vector4(0.0f, 1.0f, 1.0f, 1.0f);
			break;

		case COLOR_PURPLE:
			return vector4(0.5f, 0.0f, 1.0f, 1.0f);
			break;

		}


		return vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

}