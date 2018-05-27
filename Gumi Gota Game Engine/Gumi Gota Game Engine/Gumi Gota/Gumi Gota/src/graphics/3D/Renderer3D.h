#ifndef GUMIGOTA_RENDERER3D_H
#define GUMIGOTA_RENDERER3D_H



/* INCLUDES */
// Header Includes
#include "Scene3D.h"
#include "Model.h"
#include "Camera3D.h"

#include "../Shader.h"
#include "../Color.h"
#include "../Window.h"

#include "../../utils/Timer.h"

#include "../buffers/FrameBuffer.h"



namespace gg
{

	class Renderer3D : public Scene3D
	{
	protected:
		/* Variables */
		Shader m_basicLightShader;
		Shader m_skyboxShader;
		Shader m_normalParticleShader;
		Shader m_instanceParticleShader;
		Shader m_waterLightShader;

		float m_zNear, m_zFar;
		
		Timer m_lightTimer; //used for updating rendered lights (finding closest lights to the camera)
		float m_lightUpdateInterval; //used for storing time used for updating rendered lights (finding closest lights to the camera)

		VertexArray m_normalParticleVAO;
		VertexArray m_instanceParticleVAO;
		VertexBuffer* m_instanceVBO;

		VertexArray m_waterVAO;
		FrameBuffer m_waterReflectionFBO;
		FrameBuffer m_waterRefractionFBO;
		Texture m_waterDuDvMap;
		Texture m_waterNormalMap;

	public:
		/* Constructors */
		Renderer3D();

		/* Functions */
		void render(const Camera3D& cam);

		void updateLights(const vector3& pos);
		void setLightUpdateInterval(const float value);

		// Setters
		void setZNear(const float value);
		void setZFar(const float value);
		void setZLimits(const float near, const float far);

		void setFogDensity(const float value);
		void setFogGradient(const float value);
		void setSkyColor(const Color& color, const Window& window); //window is taken as argument to change it's clearing color (sky color)

	private:
		// Private Functions
		void m_initParticleVAOs();
		void m_initWaterStuff();

		void m_renderRenderables(const matrix4& projection, const matrix4& view);
		void m_renderSkybox(const Camera3D& cam, const matrix4& projection);
		void m_renderParticles(const matrix4& projection, const matrix4& view);
		void m_renderWater(const Camera3D& cam, const matrix4& projection, const matrix4& view);

		void m_setClippingPlaneUniforms(const vector4& plane);
		void m_updateLightUniforms(Light3D* light, const unsigned int index);

	};

}



#endif