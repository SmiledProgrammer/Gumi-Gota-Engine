
/* INCLUDES */
// Self Include
#include "Scene3D.h"

// Header Includes
#include "../../utils/Sorting.h"



namespace gg
{

	/* ADDITIONAL FUNCTIONS */
	std::vector<unsigned int> getClosestLightsIndices(const vector3& pos, const std::vector<Light3D*>& lights, const unsigned int amount)
	{
		// Init
		std::vector<float> distances;
		distances.reserve(amount);

		// Calculating Distances from Lights
		for (unsigned int i = 0; i < lights.size(); i++)
		{
			// Distance Calculating
			distances.push_back((pos - lights[ i ]->getPosition()).length());
		}

		if (lights.size() > 0)
		{
			// Getting Indices of Sorted Values
			std::vector<unsigned int> indices = quickSortIndices(distances);

			return indices;
		}


		std::vector<unsigned int> emptyVector;
		return emptyVector;
	}



	/* Constructors */
	Scene3D::Scene3D()
	{}

	/* Functions */
	void Scene3D::update(const Camera3D& cam)
	{
		// Updating Particles
		m_updateParticleGroups(cam);
	}

	unsigned int Scene3D::addRenderable(Renderable3D* renderable)
	{
		// Checking if Renderable's Model has already been added to the Vector
		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			std::vector<Renderable3D*>& modelVector = m_renderables[i]; // Getting Vector of Renderables

			if (modelVector[0]->getModel() == renderable->getModel())
			{
				// Attaching Renderable to Exisiting Model
				modelVector.push_back(renderable);

				return i;
			}
		}

		// Attaching Renderable to New Model
		std::vector<Renderable3D*> newModelVector;
		newModelVector.push_back(renderable);
		m_renderables.push_back(newModelVector);

		return m_renderables.size() - 1; //returning index of new model in the vector
	}

	void Scene3D::popBackRenderables()
	{
		m_renderables.pop_back();
	}

	void Scene3D::reserveRenderables(const unsigned int amount)
	{
		m_renderables.reserve(amount);
	}


	void Scene3D::addLight(Light3D* light)
	{
		m_lights.push_back(light);
		m_isImportantLight.push_back(false);
	}

	void Scene3D::addLight(Light3D* light, const bool isImportant)
	{
		m_lights.push_back(light);
		m_isImportantLight.push_back(isImportant);
	}

	void Scene3D::popBackLights()
	{
		m_lights.pop_back();
	}

	void Scene3D::reserveLights(const unsigned int amount)
	{
		m_lights.reserve(amount);
	}


	void Scene3D::addParticleGroup(const ParticleGroup& pg)
	{
		m_particleGroups.push_back(pg);
	}

	void Scene3D::popBackParticleGroups()
	{
		m_particleGroups.pop_back();
	}

	void Scene3D::reserveParticleGroups(const unsigned int amount)
	{
		m_particleGroups.reserve(amount);
	}


	void Scene3D::addWaterTile(WaterTile* tile)
	{
		m_waterTiles.push_back(tile);
	}

	void Scene3D::popBackWaterTiles()
	{
		m_waterTiles.pop_back();
	}

	void Scene3D::reserveWaterTiles(const unsigned int amount)
	{
		m_waterTiles.reserve(amount);
	}


	void Scene3D::setSkybox(CubeMap* skybox)
	{
		m_skybox = skybox;
	}


	void Scene3D::m_updateParticleGroups(const Camera3D& cam)
	{
		for (unsigned int i = 0; i < m_particleGroups.size(); i++)
		{
			// Updating Particles in Group
			m_particleGroups[i].update(cam);

			// Checking if All Particles from Group are Deleted
			if (m_particleGroups[i].getParticles().size() == 0)
			{
				// Deleting Particle Group
				m_particleGroups.erase(m_particleGroups.begin() + i);
			}
		}
	}

}