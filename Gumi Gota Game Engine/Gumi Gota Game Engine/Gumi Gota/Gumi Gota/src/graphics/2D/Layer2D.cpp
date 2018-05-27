
/* INCLUDES */
// Self Include
#include "Layer2D.h"

// OpenGL Includes
#include <GL/glew.h>

// Normal Includes
#include <sstream>

// Header Includes
#include "../buffers/VertexBuffer.h"

#include "../ErrorHandling.h"

#include <iostream> ///remove l8r



/* MACROS */
#define RENDERER2D_DEFAULT_LIGHT_UPDATE_INTERVAL 0.1f
#define RENDERER2D_MAX_RENDERED_LIGHTS 512



namespace gg
{

	/* ADDITIONAL STUFF */
	static float s_vboData[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
	};



	/* Constructors */
	Layer2D::Layer2D(const Window& window)
		: m_colorShader("Gumi Gota/Gumi Gota/res/shaders/Color2D.shader"),
		  m_textureShader("Gumi Gota/Gumi Gota/res/shaders/Texture2D.shader"),
		  m_colorLightShader("Gumi Gota/Gumi Gota/res/shaders/ColorLight2D.shader"),
		  m_textureLightShader("Gumi Gota/Gumi Gota/res/shaders/TextureLight2D.shader"),
		  m_projectionMatrix(matrix4::orthographic(0.0f, (float)window.getWidth(), 0.0f, (float)window.getHeight(), -1.0f, 1.0f)),
		  m_vao(),
		  m_lightUpdateInterval(RENDERER2D_DEFAULT_LIGHT_UPDATE_INTERVAL)
	{
		// Shader Setup
		m_textureShader.start();
		m_textureShader.setUniform1i("u_textureSampler", 0);
		
		m_textureLightShader.start();
		m_textureLightShader.setUniform1i("u_textureSampler", 0);
		m_textureLightShader.stop();

		// VAO Setup
		VertexBuffer* dataVBO = new VertexBuffer(s_vboData, 8, 2);
		m_vao.addAttribute(dataVBO, 0);
		VertexArray::unbind();
	}

	/* Functions */
	void Layer2D::render()
	{
		m_render(vector2(0.0f, 0.0f), false);
	}

	void Layer2D::render(const bool renderLighting)
	{
		m_render(vector2(0.0f, 0.0f), renderLighting);
	}

	void Layer2D::render(const Camera2D& cam)
	{
		m_render(cam.getPosition(), false);
	}

	void Layer2D::render(const Camera2D& cam, const bool renderLighting)
	{
		m_render(cam.getPosition(), renderLighting);
	}


	void Layer2D::updateLights(const Camera2D& cam)
	{
		// Checking If Lights Should Get Updated
		if (m_lightTimer.elapsed() >= m_lightUpdateInterval && m_lightUpdateInterval != 0.0f)
		{
			m_lightTimer.reset(); // Resetting Timer

			// Init
			unsigned int loadedLights = 0;

			// Getting Closest Lights Indices
			std::vector<unsigned int> closestLightsIndices = getClosestLightsIndices(m_lights, cam, RENDERER2D_MAX_RENDERED_LIGHTS);

			// Important Lights
			for (unsigned int i = 0; i < m_isImportantLight.size() && loadedLights < RENDERER2D_MAX_RENDERED_LIGHTS; i++)
			{
				if (m_isImportantLight[i])
				{
					// Getting Light Pointer
					Light2D* light = m_lights[i];

					// Preparing String
					std::stringstream ss;
					ss << loadedLights;

					// Uniforms Setting
					m_colorLightShader.start();
					m_colorLightShader.setUniform2f("u_lightPosition[" + ss.str() + "]", light->getPosition());
					m_colorLightShader.setUniform3f("u_lightColor[" + ss.str() + "]", light->getColor());
					m_colorLightShader.setUniform3f("u_lightAttenuation[" + ss.str() + "]", light->getAttenuation());

					m_textureLightShader.start();
					m_textureLightShader.setUniform2f("u_lightPosition[" + ss.str() + "]", light->getPosition());
					m_textureLightShader.setUniform3f("u_lightColor[" + ss.str() + "]", light->getColor());
					m_textureLightShader.setUniform3f("u_lightAttenuation[" + ss.str() + "]", light->getAttenuation());

					loadedLights++; // Updating Loaded Lights Amount
				}
			}

			// Closest Lights
			for (unsigned int i = 0; i < closestLightsIndices.size() && loadedLights < RENDERER2D_MAX_RENDERED_LIGHTS; i++)
			{
				if (!m_isImportantLight[closestLightsIndices[i]])
				{
					// Getting Light Pointer
					Light2D* light = m_lights[closestLightsIndices[i]];

					// Preparing String
					std::stringstream ss;
					ss << loadedLights;

					// Uniforms Setting
					m_colorLightShader.start();
					m_colorLightShader.setUniform2f("u_lightPosition[" + ss.str() + "]", light->getPosition());
					m_colorLightShader.setUniform3f("u_lightColor[" + ss.str() + "]", light->getColor());
					m_colorLightShader.setUniform3f("u_lightAttenuation[" + ss.str() + "]", light->getAttenuation());

					m_textureLightShader.start();
					m_textureLightShader.setUniform2f("u_lightPosition[" + ss.str() + "]", light->getPosition());
					m_textureLightShader.setUniform3f("u_lightColor[" + ss.str() + "]", light->getColor());
					m_textureLightShader.setUniform3f("u_lightAttenuation[" + ss.str() + "]", light->getAttenuation());

					loadedLights++; // Updating Loaded Lights Amount
				}

			}

			Shader::stop();
		}
	}

	void Layer2D::setLightUpdateInterval(const float value)
	{
		m_lightUpdateInterval = value;
	}

	// Private Functions
	void Layer2D::m_render(const vector2& camPos, const bool renderLighting)
	{
		// Blending Setup
		GLcall(glEnable(GL_BLEND));
		GLcall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Main Setup
		matrix4 viewMatrix = matrix4::fpsView(vector3(camPos.x, camPos.y, -0.5f), 0.0f, 0.0f);

		bool colorShaderUniformsLoaded = false;
		bool textureShaderUniformsLoaded = false;
		bool colorLightShaderUniformsLoaded = false;
		bool textureLightShaderUniformsLoaded = false;

		// Rendering Renderables from List
		for (Sprite2D* sprite : m_sprites)
		{
			// Binding
			m_vao.bind();

			// Shader Setup
			if (sprite->getTexture() == nullptr)
			{
				// Texture Setup
				Texture::unbind();

				// Uniforms Setup
				if (renderLighting)
				{
					m_colorLightShader.start();

					// First Time Uniforms Setup
					if (!colorLightShaderUniformsLoaded)
					{
						colorLightShaderUniformsLoaded = true;

						m_colorLightShader.setUniformMatrix4f("u_projectionMatrix", m_projectionMatrix);
						m_colorLightShader.setUniformMatrix4f("u_viewMatrix", viewMatrix);
					}

					// Uniforms Setup
					matrix4 model = matrix4::translation(vector3(sprite->getOrigin(), 0.0f))
						* matrix4::rotation(sprite->getRotation(), vector3(0.0f, 0.0f, 1.0f))
						* matrix4::translation(vector3(sprite->getPosition() - sprite->getOrigin(), 0.0f))
						* matrix4::scale(vector3(sprite->getSize().x, sprite->getSize().y, 1.0f));

					m_colorLightShader.setUniformMatrix4f("u_modelMatrix", model);


					const Color& renderableColor = sprite->getColor();
					m_colorLightShader.setUniform4f("u_color", renderableColor.r, renderableColor.g, renderableColor.b, renderableColor.a);
				}
				else
				{
					m_colorShader.start();

					// First Time Uniforms Setup
					if (!colorShaderUniformsLoaded)
					{
						colorShaderUniformsLoaded = true;

						m_colorShader.setUniformMatrix4f("u_projectionMatrix", m_projectionMatrix);
						m_colorShader.setUniformMatrix4f("u_viewMatrix", viewMatrix);
					}

					// Uniforms Setup
					matrix4 model = matrix4::translation(vector3(sprite->getOrigin(), 0.0f))
						* matrix4::rotation(sprite->getRotation(), vector3(0.0f, 0.0f, 1.0f))
						* matrix4::translation(vector3(sprite->getPosition() - sprite->getOrigin(), 0.0f))
						* matrix4::scale(vector3(sprite->getSize().x, sprite->getSize().y, 1.0f));

					m_colorShader.setUniformMatrix4f("u_modelMatrix", model);


					const Color& renderableColor = sprite->getColor();
					m_colorShader.setUniform4f("u_color", renderableColor.r, renderableColor.g, renderableColor.b, renderableColor.a);
				}
			}
			else
			{
				// Texture Setup
				sprite->getTexture()->bind();

				// Uniforms Setup
				if (renderLighting)
				{
					m_textureLightShader.start();

					// First Time Uniforms Setup
					if (!textureLightShaderUniformsLoaded)
					{
						textureLightShaderUniformsLoaded = true;

						m_textureLightShader.setUniformMatrix4f("u_projectionMatrix", m_projectionMatrix);
						m_textureLightShader.setUniformMatrix4f("u_viewMatrix", viewMatrix);
					}

					// Uniforms Setup
					matrix4 model = matrix4::translation(vector3(sprite->getOrigin(), 0.0f))
						* matrix4::rotation(sprite->getRotation(), vector3(0.0f, 0.0f, 1.0f))
						* matrix4::translation(vector3(sprite->getPosition() - sprite->getOrigin(), 0.0f))
						* matrix4::scale(vector3(sprite->getSize().x, sprite->getSize().y, 1.0f));

					m_textureLightShader.setUniformMatrix4f("u_modelMatrix", model);
				}
				else
				{
					m_textureShader.start();

					// First Time Uniforms Setup
					if (!textureShaderUniformsLoaded)
					{
						textureShaderUniformsLoaded = true;

						m_textureShader.setUniformMatrix4f("u_projectionMatrix", m_projectionMatrix);
						m_textureShader.setUniformMatrix4f("u_viewMatrix", viewMatrix);
					}

					// Uniforms Setup
					matrix4 model = matrix4::translation(vector3(sprite->getOrigin(), 0.0f))
						* matrix4::rotation(sprite->getRotation(), vector3(0.0f, 0.0f, 1.0f))
						* matrix4::translation(vector3(sprite->getPosition() - sprite->getOrigin(), 0.0f))
						* matrix4::scale(vector3(sprite->getSize().x, sprite->getSize().y, 1.0f));

					m_textureShader.setUniformMatrix4f("u_modelMatrix", model);
				}
			}

			// Rendering
			GLcall(glDrawArrays(GL_TRIANGLE_STRIP, 0, 8));
		}

		// Main Finishing
		GLcall(glDisable(GL_BLEND));

		VertexArray::unbind();

		Shader::stop();
	}

}