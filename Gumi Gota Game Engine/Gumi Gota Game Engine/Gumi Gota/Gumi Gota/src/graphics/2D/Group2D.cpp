
/* INCLUDES */
// Self Include
#include "Group2D.h"



namespace gg
{

	/* Constructors */
	Group2D::Group2D()
	{}

	/* Functions */
	void Group2D::addSprite(Sprite2D* sprite)
	{
		m_sprites.push_back(sprite);
	}

	void Group2D::addLight(Light2D* light)
	{
		m_lights.push_back(light);
	}


	void Group2D::popBackSprites()
	{
		m_sprites.pop_back();
	}

	void Group2D::popBackLights()
	{
		m_lights.pop_back();
	}


	void Group2D::reserveSprites(const unsigned int size)
	{
		m_sprites.reserve(size);
	}

	void Group2D::reserveLights(const unsigned int size)
	{
		m_lights.reserve(size);
	}


	void Group2D::rotate(const float rot) /// to do!!!
	{

	}

	void Group2D::move(const vector2& movement)
	{
		for (Sprite2D* sprite : m_sprites)
		{
			sprite->move(movement);
		}

		for (Light2D* light : m_lights)
		{
			light->move(movement);
		}
	}

}