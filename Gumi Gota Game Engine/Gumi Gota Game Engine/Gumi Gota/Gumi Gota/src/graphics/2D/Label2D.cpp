
/* INCLUDES */
// Self Include
#include "Label2D.h"



namespace gg
{

	/* Constructors */
	Label2D::Label2D(const std::string& text, const vector2& pos)
		: Renderable2D(pos, vector2(1.0f, 1.0f))
	{}

	Label2D::Label2D(const std::string& text, const vector2& pos, const Color& color)
		: Renderable2D(pos, vector2(1.0f, 1.0f)), m_color(color)
	{}

	/* Functions */
	void Label2D::setColor(const Color& color)
	{
		m_color = color;
	}

}