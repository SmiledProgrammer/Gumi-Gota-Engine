
/* INCLUDES */
// Self Include
#include "CubeMap.h"

// OpenGL Includes
#include <GL/glew.h>

// STBI Image Includes
#include <stb_image.h>

// Header Includes
#include "../ErrorHandling.h"

#include "../../Log.h"



/* MACROS */
#define SKYBOX_DEFAULT_SIZE 1.0f



namespace gg
{

	/* Constructors */
	CubeMap::CubeMap(const char* top, const char* bottom, const char* left, const char* right, const char* front, const char* back)
		: m_vao(), m_size(SKYBOX_DEFAULT_SIZE)
	{
		init(top, bottom, left, right, front, back);
	}

	CubeMap::CubeMap(const char* top, const char* bottom, const char* left, const char* right, const char* front, const char* back, const float m_size)
		: m_vao(), m_size(m_size)
	{
		init(top, bottom, left, right, front, back);
	}

	/* Functions */
	void CubeMap::bind() const
	{
		// Binding VAO
		m_vao.bind();

		// Binding Texture
		GLcall(glActiveTexture(GL_TEXTURE0));
		GLcall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapID));
	}

	void CubeMap::bind(const unsigned int slot) const
	{
		// Binding VAO
		m_vao.bind();

		// Binding Texture
		if (slot < 32)
		{
			GLcall(glActiveTexture(GL_TEXTURE0 + slot));
			GLcall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapID));
		}
		else
		{
			LOG("[Error] Texture Slot is out of range.");
		}
	}

	void CubeMap::unbind()
	{
		// Unbinding VAO
		VertexArray::unbind();

		// Unbinding Texture
		GLcall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}

	// Setters
	void CubeMap::setSize(const float size)
	{
		m_size = size;
	}

	// Private Functions
	void CubeMap::init(const char* top, const char* bottom, const char* left, const char* right, const char* front, const char* back)
	{
		/* Buffers Setup */
		// Vertices Setup
		float cubeVertices[] = {
			-m_size,  m_size, -m_size,
			-m_size, -m_size, -m_size,
			 m_size, -m_size, -m_size,
			 m_size, -m_size, -m_size,
			 m_size,  m_size, -m_size,
			-m_size,  m_size, -m_size,

			-m_size, -m_size,  m_size,
			-m_size, -m_size, -m_size,
			-m_size,  m_size, -m_size,
			-m_size,  m_size, -m_size,
			-m_size,  m_size,  m_size,
			-m_size, -m_size,  m_size,

			 m_size, -m_size, -m_size,
			 m_size, -m_size,  m_size,
			 m_size,  m_size,  m_size,
			 m_size,  m_size,  m_size,
			 m_size,  m_size, -m_size,
			 m_size, -m_size, -m_size,

			-m_size, -m_size,  m_size,
			-m_size,  m_size,  m_size,
			 m_size,  m_size,  m_size,
			 m_size,  m_size,  m_size,
			 m_size, -m_size,  m_size,
			-m_size, -m_size,  m_size,

			-m_size,  m_size, -m_size,
			 m_size,  m_size, -m_size,
			 m_size,  m_size,  m_size,
			 m_size,  m_size,  m_size,
			-m_size,  m_size,  m_size,
			-m_size,  m_size, -m_size,

			-m_size, -m_size, -m_size,
			-m_size, -m_size,  m_size,
			 m_size, -m_size, -m_size,
			 m_size, -m_size, -m_size,
			-m_size, -m_size,  m_size,
			 m_size, -m_size,  m_size
		};

		// Creating VBO
		VertexBuffer* positionsVBO = new VertexBuffer(cubeVertices, 108, 3);

		// Attaching VBO to VAO
		m_vao.addAttribute(positionsVBO, 0);

		// Finishing
		VertexArray::unbind();

		/* Cube Map Setup */
		// Init
		unsigned char* textureData;
		int width, height;
		int BPP;

		// Creating Cube Map
		GLcall(glGenTextures(1, &m_cubeMapID));
		///GLcall(glActiveTexture(GL_TEXTURE0)); ///check l8r if it's needed
		GLcall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapID));

		// Textures Setup
		GLcall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLcall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLcall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLcall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLcall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

		// Loading Textures
		stbi_set_flip_vertically_on_load(0);

		for (unsigned int i = 0; i < 6; i++)
		{
			// Getting Current Texture Filepath
			const char* currentTexture = front;
			switch (i)
			{
			case 1 : currentTexture = back;  break;
			case 2 : currentTexture = top;    break;
			case 3 : currentTexture = bottom; break;
			case 4 : currentTexture = right;  break;
			case 5 : currentTexture = left;   break;
			}

			// Loading Image
			textureData = stbi_load(currentTexture, &width, &height, &BPP, 4);

			if (!textureData)
				LOG("[Error] Couldn't load texture '" << currentTexture << "'.");

			// Loading Texture to Cube Map
			GLcall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData));

			// Freeing Data
			stbi_image_free(textureData);
		}

		// Finishing
		GLcall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

	}

}