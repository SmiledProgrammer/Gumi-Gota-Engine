
/* INCLUDES */
// Self Include
#include "Texture.h"

// OpenGL Includes
#include <GL/glew.h>

// STBI Image Includes
#include <stb_image.h>

// Header Includes
#include "ErrorHandling.h"

#include "../Log.h"



namespace gg
{

	/* Constructors */
	Texture::Texture(const std::string& filepath)
		: m_textureID(0),
		  m_atlasRows(1)
	{
		m_loadImage(filepath);
	}

	Texture::Texture(const std::string& filepath, const unsigned int atlasRows)
		: m_textureID(0),
		  m_atlasRows(atlasRows)
	{
		m_loadImage(filepath);
	}

	Texture::Texture(const unsigned int textureID, const unsigned int width, const unsigned int height)
		: m_textureID(textureID),
		  m_width(width), m_height(height),
		  m_atlasRows(1)
	{}

	/* Destructor */
	Texture::~Texture()
	{
		GLcall(glDeleteTextures(1, &m_textureID));
	}

	/* Functions */
	void Texture::bind() const
	{
		GLcall(glActiveTexture(GL_TEXTURE0));
		GLcall(glBindTexture(GL_TEXTURE_2D, m_textureID));
	}

	void Texture::bind(const unsigned int slot) const
	{
		if (slot < 32)
		{
			GLcall(glActiveTexture(GL_TEXTURE0 + slot));
			GLcall(glBindTexture(GL_TEXTURE_2D, m_textureID));
		}
		else
		{
			LOG("[Error] Texture Slot is out of range.");
		}
	}

	void Texture::unbind()
	{
		GLcall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	// Private Functions
	void Texture::m_loadImage(const std::string& filepath)
	{
		// Init
		unsigned char* m_textureData;
		int m_BPP;

		// Loading Image
		stbi_set_flip_vertically_on_load(1);
		m_textureData = stbi_load(filepath.c_str(), &m_width, &m_height, &m_BPP, 4);

		if (!m_textureData)
			LOG("[Error] Couldn't load texture '" << filepath << "'.");

		// Creating Texture
		GLcall(glGenTextures(1, &m_textureID));
		GLcall(glBindTexture(GL_TEXTURE_2D, m_textureID));

		// Texture Setup
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLcall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		// Loading Up Data
		GLcall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_textureData));

		// Finishing
		GLcall(glBindTexture(GL_TEXTURE_2D, 0));

		// Freeing Data
		stbi_image_free(m_textureData);
	}

	// Setters
	void Texture::setAtlasRows(const unsigned int amount)
	{
		m_atlasRows = amount;
	}

}