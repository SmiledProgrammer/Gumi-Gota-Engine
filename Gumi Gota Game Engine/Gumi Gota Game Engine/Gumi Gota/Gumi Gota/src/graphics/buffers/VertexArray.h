#ifndef GUMIGOTA_VERTEXARRAY_H
#define GUMIGOTA_VERTEXARRAY_H



/* INCLUDES */
// Normal Includes
#include <vector>

// Header Includes
#include "VertexBuffer.h"



namespace gg
{

	class VertexArray
	{
	private:
		/* Variables */
		unsigned int m_id;
		std::vector<VertexBuffer*> m_buffers;

	public:
		/* Constructors */
		VertexArray();

		/* Destructor */
		~VertexArray();

		/* Functions */
		void addAttribute(VertexBuffer* vbo, const unsigned int index);
		void addAttribute(VertexBuffer* vbo, const unsigned int index, const unsigned int stride); //stride is in floats amount
		void addInstancedAttribute(VertexBuffer* vbo, const unsigned int index, const unsigned int dataLength, const unsigned int stride, const unsigned int offset); //stride is in floats amount; offset is in floats amount

		void bind() const;
		static void unbind();

		// Getters
		inline unsigned int getID() const {	return m_id; }

	private:
		// Private Functions
		void m_addBuffer(VertexBuffer* vbo);

	};

}



#endif