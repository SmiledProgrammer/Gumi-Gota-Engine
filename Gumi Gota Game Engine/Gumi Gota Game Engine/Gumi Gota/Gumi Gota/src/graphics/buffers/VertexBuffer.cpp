
/* INCLUDES */
// Self Include
#include "VertexBuffer.h"

// OpenGL Includes
#include "GL/glew.h"

// Header Includes
#include "../../graphics/ErrorHandling.h"



namespace gg
{

	/* Constructors */
	VertexBuffer::VertexBuffer(const void* data, const unsigned int size, const unsigned int componentCount)
		: m_componentCount(componentCount)
	{
		GLcall(glGenBuffers(1, &m_id));
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_id));

		// Buffering Data
		GLcall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW));

		GLcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBuffer::VertexBuffer(const void* data, const unsigned int size, const unsigned int componentCount, VertexBufferDrawType usage)
		: m_componentCount(componentCount)
	{
		GLcall(glGenBuffers(1, &m_id));
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_id));

		// Buffering Data
		switch (usage)
		{

		case VERTEX_BUFFER_STATIC_DRAW:
			GLcall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW));
			break;

		case VERTEX_BUFFER_DYNAMIC_DRAW:
			GLcall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_DYNAMIC_DRAW));
			break;

		case VERTEX_BUFFER_STREAM_DRAW:
			GLcall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STREAM_DRAW));
			break;

		}

		GLcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	/* Destructor */
	VertexBuffer::~VertexBuffer()
	{
		GLcall(glDeleteBuffers(1, &m_id));
	}

	/* Functions */
	void VertexBuffer::bufferData(const void* data, const unsigned int size)
	{
		GLcall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW));
	}

	void VertexBuffer::bufferData(const void* data, const unsigned int size, VertexBufferDrawType usage)
	{
		switch (usage)
		{

		case VERTEX_BUFFER_STATIC_DRAW:
			GLcall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW));
			break;

		case VERTEX_BUFFER_DYNAMIC_DRAW:
			GLcall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_DYNAMIC_DRAW));
			break;

		case VERTEX_BUFFER_STREAM_DRAW:
			GLcall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STREAM_DRAW));
			break;

		}
	}

	void VertexBuffer::bufferSubData(const void* data, const unsigned int size)
	{
		GLcall(glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(float), data));
	}


	void VertexBuffer::bind() const
	{
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
	}

	void VertexBuffer::unbind()
	{
		GLcall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

}