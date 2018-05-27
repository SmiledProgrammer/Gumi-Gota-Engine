#ifndef GUMIGOTA_MODEL_H
#define GUMIGOTA_MODEL_H



/* INCLUDES */
// Header Includes
#include "../buffers/VertexArray.h"
#include "../buffers/IndexBuffer.h"

#include "../Texture.h"



namespace gg
{

	class Model
	{
	protected:
		/* Variables */
		unsigned int m_vertexCount;

		VertexArray m_vao;
		IndexBuffer m_ibo;

		Texture m_texture;

		float m_shineDamper;
		float m_reflectivity;

		bool m_hasTransparency;
		bool m_hasFakeLighting;

	public:
		/* Constructors */
		Model(const float* vertices, const unsigned int vertexCount, const float* texCoords, const unsigned int texCoordsCount, const std::string& textureFilepath, const float* normals, const unsigned int normalCount, const unsigned int* indices, const unsigned int indexCount);
		Model(const float* vertices, const unsigned int vertexCount, const float* texCoords, const unsigned int texCoordsCount, const std::string& textureFilepath, const float* normals, const unsigned int normalCount, const unsigned int* indices, const unsigned int indexCount, const float shineDamper, const float reflectivity);

		/* Functions */
		void bind() const;
		static void unbind();

		// Setters
		void setShineDamper(const float value);
		void setReflectivity(const float value);

		void setHasTransparency(const bool value);
		void setHasFakeLighting(const bool value);
		
		void setTextureRows(const unsigned int amount);

		// Getters
		inline unsigned int getVertexCount() const { return m_vertexCount; }

		inline float getShineDamper()  const { return m_shineDamper;  }
		inline float getReflectivity() const { return m_reflectivity; }

		inline bool hasTransparency() const { return m_hasTransparency; }
		inline bool hasFakeLighting() const { return m_hasFakeLighting; }
		
		inline unsigned int getTextureRows() const { return m_texture.getAtlasRows(); }

	};

}



#endif