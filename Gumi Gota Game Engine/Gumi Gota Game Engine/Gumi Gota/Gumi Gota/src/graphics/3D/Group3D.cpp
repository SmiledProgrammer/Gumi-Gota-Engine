
/* INCLUDES */
// Self Include
#include "Group3D.h"



namespace gg
{

	/* Constructors */
	Group3D::Group3D()
	{}

	/* Functions */
	void Group3D::addRenderable(Renderable3D* renderable)
	{
		m_renderables.push_back(renderable);
	}

	void Group3D::addLight(Light3D* light)
	{
		m_lights.push_back(light);
	}


	void Group3D::popBackRenderables()
	{
		m_renderables.pop_back();
	}

	void Group3D::popBackLights()
	{

	}


	void Group3D::reserveRenderables(const unsigned int size)
	{
		m_renderables.reserve(size);
	}

	void Group3D::reserveLights(const unsigned int size)
	{
		m_lights.reserve(size);
	}


	void Group3D::rotate(const vector3& rot) /// to do!!!
	{

	}

	void Group3D::move(const vector3& movement)
	{
		for (Renderable3D* renderable : m_renderables)
		{
			renderable->move(movement);
		}

		for (Light3D* light : m_lights)
		{
			light->move(movement);
		}
	}

}