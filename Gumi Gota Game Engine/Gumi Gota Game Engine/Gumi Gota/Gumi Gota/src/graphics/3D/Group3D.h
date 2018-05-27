#ifndef GUMIGOTA_GROUP3D_H
#define GUMIGOTA_GROUP3D_H



/* INCLUDES */
// Normal Includes
#include <vector>

// Header Includes
#include "Renderable3D.h"
#include "Light3D.h"



namespace gg
{

	class Group3D
	{
	protected:
		/* Variables */
		std::vector<Renderable3D*> m_renderables;
		std::vector<Light3D*> m_lights;

	public:
		/* Constructors */
		Group3D();

		/* Functions */
		void addRenderable(Renderable3D* renderable);
		virtual void addLight(Light3D* light);

		void popBackRenderables();
		void popBackLights();

		void reserveRenderables(const unsigned int size);
		void reserveLights(const unsigned int size);


		virtual void move(const vector3& movement);
		virtual void rotate(const vector3& rot); //rotation is given in radians

		// Getters
		inline const std::vector<Renderable3D*>& getRenderables() const { return m_renderables; }
		inline const std::vector<Light3D*>&      getLights()      const { return m_lights;      }

	};

}



#endif