#ifndef GUMIGOTA_LABEL2D_H
#define GUMIGOTA_LABEL2D_H



/* INCLUDES */
// Normal Includes
#include <string>

// Header Includes
#include "Renderable2D.h"

#include "../Color.h"



namespace gg
{

	class Label2D : public Renderable2D
	{
	protected:
		/* Variables */
		std::string m_text;
		Color m_color;

	public:
		/* Constructors */
		Label2D(const std::string& text, const vector2& pos);
		Label2D(const std::string& text, const vector2& pos, const Color& color);

		/* Functions */
		void setColor(const Color& color);

	};

}



#endif