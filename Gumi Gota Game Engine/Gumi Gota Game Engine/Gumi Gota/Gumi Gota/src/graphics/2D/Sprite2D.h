#ifndef GUMIGOTA_SPRITE2D_H
#define GUMIGOTA_SPRITE2D_H



/* INCLUDES */
// Header Includes
#include "Renderable2D.h"

#include "../Texture.h"
#include "../Color.h"



namespace gg
{

	class Sprite2D : public Renderable2D
	{
	protected:
		/* Variables */
		Color m_color;
		Texture* m_texture;

	public:
		/* Constructors */
		Sprite2D(const vector2& pos, const vector2& size); //default constructor
		Sprite2D(const vector2& pos, const vector2& size, const float rot); //all parameters constructor

		/* Functions */
		// Setters
		void setColor(const Color& color); //changes color of rendered object
		void setTexture(Texture* tex); //changes texture of rendered object

		// Getters
		inline const Color& getColor() const { return m_color; }
		inline Texture* getTexture() const { return m_texture; }

	};

}



#endif