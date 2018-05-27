
/* INCLUDES */
// Self Include
#include "Light2D.h"



/* MACROS */
#define LIGHT2D_DEFAULT_ATTENUATION vector3(1.0f, 0.01f, 0.0001f)
#define LIGHT2D_DEFAULT_COLOR COLOR_WHITE



namespace gg
{

	/* Constructors */
	Light2D::Light2D(const vector2& pos)
		: m_position(pos), m_color(LIGHT2D_DEFAULT_COLOR), m_attenuation(LIGHT2D_DEFAULT_ATTENUATION)
	{}

	Light2D::Light2D(const vector2& pos, const Color& color)
		: m_position(pos), m_color(color), m_attenuation(LIGHT2D_DEFAULT_ATTENUATION)
	{}

	Light2D::Light2D(const vector2& pos, const Color& color, const vector3& attenuation)
		: m_position(pos), m_color(color), m_attenuation(attenuation)
	{}

	/* Functions */
	void Light2D::move(const vector2& movement)
	{
		m_position += movement;
	}

	void Light2D::setPosition(const vector2& pos)
	{
		m_position = pos;
	}


	void Light2D::setColor(const Color& color)
	{
		m_color = color;
	}


	void Light2D::increaseAttenuation(const vector3& value)
	{
		m_attenuation += value;
	}

	void Light2D::setAttenuation(const vector3& value)
	{
		m_attenuation = value;
	}

}