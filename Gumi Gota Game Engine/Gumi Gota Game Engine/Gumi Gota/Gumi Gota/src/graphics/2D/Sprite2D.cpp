
/* INCLUDES */
// Self Include
#include "Sprite2D.h"



namespace gg
{

	/* Constructors */
	Sprite2D::Sprite2D(const vector2& pos, const vector2& size)
		: Renderable2D(pos, size),
		  m_texture(nullptr)
	{}

	Sprite2D::Sprite2D(const vector2& pos, const vector2& size, const float rot)
		: Renderable2D(pos, size, rot),
		  m_texture(nullptr)
	{}

	/* Functions */
	// Setters
	void Sprite2D::setColor(const Color& color)
	{
		m_color = color;
	}

	void Sprite2D::setTexture(Texture* tex)
	{
		m_texture = tex;
	}

}