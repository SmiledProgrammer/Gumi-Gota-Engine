/* INCLUDES */
// Self Include
#include "Light3D.h"



/* MACROS */
#define LIGHT3D_DEFAULT_ATTENUATION vector3(1.0f, 0.01f, 0.001f)
#define LIGHT3D_DEFAULT_COLOR COLOR_WHITE



namespace gg
{

	/* Constructors */
	Light3D::Light3D(const vector3& pos)
		: m_position(pos), m_color(LIGHT3D_DEFAULT_COLOR), m_attenuation(LIGHT3D_DEFAULT_ATTENUATION)
	{}

	Light3D::Light3D(const vector3& pos, const Color& color)
		: m_position(pos), m_color(color), m_attenuation(LIGHT3D_DEFAULT_ATTENUATION)
	{}

	Light3D::Light3D(const vector3& pos, const Color& color, const vector3& attenuation)
		: m_position(pos), m_color(color), m_attenuation(attenuation)
	{}

	/* Functions */
	void Light3D::move(const vector3& movement)
	{
		m_position += movement;
	}

	void Light3D::setPosition(const vector3& pos)
	{
		m_position = pos;
	}


	void Light3D::setColor(const Color& color)
	{
		m_color = color;
	}


	void Light3D::increaseAttenuation(const vector3& value)
	{
		m_attenuation += value;
	}

	void Light3D::setAttenuation(const vector3& value)
	{
		m_attenuation = value;
	}

}