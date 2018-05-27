
/* INCLUDES */
// Self Include
#include "Camera2D.h"



namespace gg
{

	/* Constructors */
	Camera2D::Camera2D(const vector2& pos, const vector2& displaySize)
		: m_position(pos - displaySize / 2), m_halfOfDisplaySize(displaySize / 2)
	{}

	/* Functions */
	void Camera2D::move(const vector2& movement)
	{
		m_position += movement;
	}

	void Camera2D::setPosition(const vector2& pos)
	{
		m_position = pos - m_halfOfDisplaySize;
	}

}