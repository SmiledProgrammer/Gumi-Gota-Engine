#ifndef GUMIGOTA_GROUP2D_H
#define GUMIGOTA_GROUP2D_H



/* INCLUDES */
// Normal Includes
#include <vector>

// Header Includes
#include "Light2D.h"
#include "Sprite2D.h"
#include "Camera2D.h"



namespace gg
{

	class Group2D
	{
	protected:
		/* Variables */
		std::vector<Sprite2D*> m_sprites;
		std::vector<Light2D*> m_lights;

	public:
		/* Constructors */
		Group2D();

		/* Functions */
		void addSprite(Sprite2D* sprite);
		void addLight(Light2D* light);

		void popBackSprites();
		void popBackLights();

		void reserveSprites(const unsigned int size);
		void reserveLights(const unsigned int size);


		virtual void move(const vector2& movement);
		virtual void rotate(const float rot); //rotation is given in radians

		// Getters
		inline const std::vector<Sprite2D*>& getSprites() const { return m_sprites; }
		inline const std::vector<Light2D*>&  getLights()  const { return m_lights;  }

	};

}



#endif