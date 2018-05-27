
/* INCLUDES */
// Self Include
#include "Scene2D.h"

// Header Includes
#include "../../utils/Sorting.h"



namespace gg
{

	/* Constructors */
	Scene2D::Scene2D()
	{}

	/* Functions */
	void Scene2D::addSprite(Sprite2D* sprite)
	{
		m_sprites.push_back(sprite);
	}

	void Scene2D::popBackSprites()
	{
		m_sprites.pop_back();
	}

	void Scene2D::reserveSprites(const unsigned int size)
	{
		m_sprites.reserve(size);
	}


	void Scene2D::addLight(Light2D* light)
	{
		m_lights.push_back(light);
		m_isImportantLight.push_back(false);
	}

	void Scene2D::addLight(Light2D* light, const bool isImportant)
	{
		m_lights.push_back(light);
		m_isImportantLight.push_back(isImportant);
	}

	void Scene2D::popBackLights()
	{
		m_lights.pop_back();
	}

	void Scene2D::reserveLights(const unsigned int size)
	{
		m_lights.reserve(size);
	}



	/* ADDITIONAL FUNCTIONS */
	std::vector<unsigned int> getClosestLightsIndices(const std::vector<Light2D*>& lights, const Camera2D& cam, const unsigned int amount)
	{
		// Init
		std::vector<float> distances;
		distances.reserve(amount);

		vector2 transformedCamPos = cam.getPosition() + cam.getHalfOfDisplaySize();

		// Calculating Distances from Lights
		for (unsigned int i = 0; i < lights.size(); i++)
		{
			// Distance Calculating
			distances.push_back((transformedCamPos - lights[i]->getPosition()).length());
		}

		// Getting Indices of Sorted Values
		std::vector<unsigned int> indices = quickSortIndices(distances);


		return indices;
	}


}