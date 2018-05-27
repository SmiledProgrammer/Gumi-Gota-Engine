
/* INCLUDES */
// Self Include
#include "Model.h"

// Header Includes
#include "../buffers/VertexBuffer.h"



/* MACROS */
#define MODEL_DEFAULT_SHINE_DAMPER 10.0f
#define MODEL_DEFAULT_REFLECTIVITY 1.0f

#define MODEL_DEFAULT_HAS_TRANSPARENCY false
#define MODEL_DEFAULT_HAS_FAKE_LIGHTING false



namespace gg
{

	/* Constructors */
	Model::Model(const float* vertices, const unsigned int vertexCount, const float* texCoords, const unsigned int texCoordsCount, const std::string& textureFilepath, const float* normals, const unsigned int normalCount, const unsigned int* indices, const unsigned int indexCount)
		: m_vertexCount(indexCount),
		  m_vao(), m_ibo(indices, indexCount),
		  m_texture(textureFilepath),
		  m_shineDamper(MODEL_DEFAULT_SHINE_DAMPER), m_reflectivity(MODEL_DEFAULT_REFLECTIVITY),
		  m_hasTransparency(MODEL_DEFAULT_HAS_TRANSPARENCY), m_hasFakeLighting(MODEL_DEFAULT_HAS_FAKE_LIGHTING)
	{
		// Creating Vertex Buffers
		VertexBuffer* positionsVBO = new VertexBuffer(vertices, vertexCount, 3);
		VertexBuffer* textureCoordinatesVBO = new VertexBuffer(texCoords, texCoordsCount, 2);
		VertexBuffer* normalsVBO = new VertexBuffer(normals, normalCount, 3);

		// Attaching VBOs to VAO
		m_vao.addAttribute(positionsVBO, 0);
		m_vao.addAttribute(textureCoordinatesVBO, 1);
		m_vao.addAttribute(normalsVBO, 2);

		// Finishing
		VertexArray::unbind();
	}

	Model::Model(const float* vertices, const unsigned int vertexCount, const float* texCoords, const unsigned int texCoordsCount, const std::string& textureFilepath, const float* normals, const unsigned int normalCount, const unsigned int* indices, const unsigned int indexCount, const float shineDamper, const float reflectivity)
		: m_vertexCount(indexCount),
		  m_vao(), m_ibo(indices, indexCount),
		  m_texture(textureFilepath),
		  m_shineDamper(shineDamper), m_reflectivity(reflectivity),
		  m_hasTransparency(MODEL_DEFAULT_HAS_TRANSPARENCY), m_hasFakeLighting(MODEL_DEFAULT_HAS_FAKE_LIGHTING)
	{
		// Creating Vertex Buffers
		VertexBuffer* positionsVBO = new VertexBuffer(vertices, vertexCount, 3);
		VertexBuffer* textureCoordinatesVBO = new VertexBuffer(texCoords, texCoordsCount, 2);
		VertexBuffer* normalsVBO = new VertexBuffer(normals, normalCount, 3);

		// Attaching VBOs to VAO
		m_vao.addAttribute(positionsVBO, 0);
		m_vao.addAttribute(textureCoordinatesVBO, 1);
		m_vao.addAttribute(normalsVBO, 2);

		// Finishing
		VertexArray::unbind();
	}

	/* Functions */
	void Model::bind() const
	{
		m_vao.bind();
		m_ibo.bind();

		m_texture.bind();
	}

	void Model::unbind()
	{
		VertexArray::unbind();
		IndexBuffer::unbind();

		Texture::unbind();
	}

	// Setters
	void Model::setShineDamper(const float value)
	{
		m_shineDamper = value;
	}

	void Model::setReflectivity(const float value)
	{
		m_reflectivity = value;
	}


	void Model::setHasTransparency(const bool value)
	{
		m_hasTransparency = value;
	}

	void Model::setHasFakeLighting(const bool value)
	{
		m_hasFakeLighting = value;
	}


	void Model::setTextureRows(const unsigned int amount)
	{
		m_texture.setAtlasRows(amount);
	}

}