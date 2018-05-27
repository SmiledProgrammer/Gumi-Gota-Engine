#ifndef GUMIGOTA_SCENE2D_H
#define GUMIGOTA_SCENE2D_H



/* INCLUDES */
// Normal Includes
#include <vector>

// Header Includes
#include "Light2D.h"
#include "Sprite2D.h"
#include "Camera2D.h"

#include "../../utils/Timer.h"



namespace gg
{

	class Scene2D
	{
	protected:
		/* Variables */
		std::vector<Sprite2D*> m_sprites;

		std::vector<Light2D*> m_lights;
		std::vector<bool> m_isImportantLight; //used for lights that are forced to be rendered
		Timer m_lightTimer; //used for updating rendered lights (finding closest lights to the camera)
		float m_lightUpdateInterval; //used for storing time used for updating rendered lights (finding closest lights to the camera)

	public:
		/* Constructors */
		Scene2D();

		/* Functions */
		void addSprite(Sprite2D* sprite);
		void popBackSprites();
		void reserveSprites(const unsigned int size);

		void addLight(Light2D* light);
		void addLight(Light2D* light, const bool isImportant); //if is isImportant is true light will be forced to be rendered
		void popBackLights();
		void reserveLights(const unsigned int size);

	};



	/* ADDITIONAL FUNCTIONS */
	std::vector<unsigned int> getClosestLightsIndices(const std::vector<Light2D*>& lights, const Camera2D& cam, const unsigned int amount);

}



#endif