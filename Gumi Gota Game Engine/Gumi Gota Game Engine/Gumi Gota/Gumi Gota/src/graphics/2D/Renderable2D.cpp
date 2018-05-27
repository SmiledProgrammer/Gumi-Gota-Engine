
/* INCLUDES */
// Self Include
#include "Renderable2D.h"

// Header Includes
#include "../buffers/VertexBuffer.h"



namespace gg
{

	/* Constructors */
	Renderable2D::Renderable2D(const vector2& pos, const vector2& size)
		: m_position(pos - size / 2), m_size(size), m_rotation(0.0f), m_origin(pos)
	{}

	Renderable2D::Renderable2D(const vector2& pos, const vector2& size, const float rot)
		: m_position(pos - size / 2), m_size(size), m_rotation(rot), m_origin(pos)
	{}

	/* Functions */
	// Setters
	void Renderable2D::move(const vector2& movement)
	{
		m_position += movement;
		m_origin += movement;
	}

	void Renderable2D::addSize(const vector2& size)
	{
		m_size += size;
	}

	void Renderable2D::rotate(const float rot)
	{
		m_rotation += rot;
	}

	void Renderable2D::moveOrigin(const vector2& movement)
	{
		m_origin += movement;
	}


	void Renderable2D::setPosition(const vector2& pos)
	{
		m_position = pos;
		m_origin += pos;
	}

	void Renderable2D::setSize(const vector2& size)
	{
		m_size = size;
	}

	void Renderable2D::setRotation(const float rot)
	{
		m_rotation = rot;
	}

	void Renderable2D::setOrigin(const vector2& origin)
	{
		m_origin = origin;
	}

}