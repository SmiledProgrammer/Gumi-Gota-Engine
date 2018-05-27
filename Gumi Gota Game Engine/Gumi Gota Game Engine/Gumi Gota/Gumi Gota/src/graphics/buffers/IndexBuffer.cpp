
/* INCLUDES */
// Self include
#include "IndexBuffer.h"

// OpenGL Includes
#include "GL/glew.h"

// Header Includes
#include "../../graphics/ErrorHandling.h"



namespace gg
{

	/* Constructors */
	IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count)
		: m_count(count)
	{
		GLcall(glGenBuffers(1, &m_id));
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
		bufferData(data, count, INDEX_BUFFER_DRAW_STATIC);
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count, IndexBufferDrawType usage)
		: m_count(count)
	{
		GLcall(glGenBuffers(1, &m_id));
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
		bufferData(data, count, usage);
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	/* Destructor */
	IndexBuffer::~IndexBuffer()
	{
		GLcall(glDeleteBuffers(1, &m_id));
	}

	/* Functions */
	void IndexBuffer::bufferData(const unsigned int* data, const unsigned int count)
	{
		m_count = count;

		if (data != nullptr)
		{
			GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
			GLcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
			GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}
	}

	void IndexBuffer::bufferData(const unsigned int* data, const unsigned int count, IndexBufferDrawType usage)
	{
		m_count = count;

		if (data != nullptr)
		{
			switch (usage)
			{

			case INDEX_BUFFER_DRAW_STATIC:
				GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
				GLcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
				GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
				break;

			case INDEX_BUFFER_DRAW_DYNAMIC:
				GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
				GLcall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW));
				GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
				break;

			}
		}
	}


	void IndexBuffer::bind() const
	{
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
	}

	void IndexBuffer::unbind()
	{
		GLcall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}