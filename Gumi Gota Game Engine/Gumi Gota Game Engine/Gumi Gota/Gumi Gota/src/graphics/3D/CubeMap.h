#ifndef GUMIGOTA_CUBE_MAP_H
#define GUMIGOTA_CUBE_MAP_H



/* INCLUDES */
// Header Includes
#include "../buffers/VertexArray.h"
#include "../buffers/VertexBuffer.h"

#include "../Texture.h"



namespace gg
{

	class CubeMap
	{
	protected:
		/* Variables */
		unsigned int m_cubeMapID;
		float m_size;

		VertexArray m_vao;

	public:
		/* Constructors */
		CubeMap(const char* top, const char* bottom, const char* left, const char* right, const char* front, const char* back);
		CubeMap(const char* top, const char* bottom, const char* left, const char* right, const char* front, const char* back, const float size);

		/* Functions */
		void bind() const;
		void bind(const unsigned int slot) const;
		static void unbind();

		// Setters
		void setSize(const float size);

		// Getters
		inline unsigned int getID()   const { return m_cubeMapID; }
		inline float        getSize() const { return m_size;      }

	protected:
		// Private Functions
		void init(const char* top, const char* bottom, const char* left, const char* right, const char* front, const char* back);

	};

}



#endif