
/* INCLUDES */
// Self Include
#include "VertexArray.h"

// OpenGL Includes
#include "GL/glew.h"

// Header Includes
#include "../../graphics/ErrorHandling.h"

#include <iostream> ///remove l8r



namespace gg
{

	/* Constructors */
	VertexArray::VertexArray()
	{
		GLcall(glGenVertexArrays(1, &m_id));
		GLcall(glBindVertexArray(m_id));
	}

	/* Destructor */
	VertexArray::~VertexArray()
	{
		for (VertexBuffer* vbo : m_buffers)
		{
			delete vbo;
		}

		GLcall(glDeleteVertexArrays(1, &m_id));
	}

	/* Functions */
	void VertexArray::addAttribute(VertexBuffer* vbo, const unsigned int index)
	{
		bind();
		vbo->bind();

		GLcall(glEnableVertexAttribArray(index));
		GLcall(glVertexAttribPointer(index, vbo->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0));

		m_addBuffer(vbo);
		
		vbo->unbind();
		unbind();
	}

	void VertexArray::addAttribute(VertexBuffer* vbo, const unsigned int index, const unsigned int stride)
	{
		bind();
		vbo->bind();

		GLcall(glEnableVertexAttribArray(index));
		GLcall(glVertexAttribPointer(index, vbo->getComponentCount(), GL_FLOAT, GL_FALSE, stride * sizeof(float), 0));

		m_addBuffer(vbo);

		vbo->unbind();
		unbind();
	}

	void VertexArray::addInstancedAttribute(VertexBuffer* vbo, const unsigned int index, const unsigned int dataLength, const unsigned int stride, const unsigned int offset)
	{
		bind();
		vbo->bind();

		GLcall(glEnableVertexAttribArray(index));
		GLcall(glVertexAttribPointer(index, dataLength, GL_FLOAT, GL_FALSE, stride * sizeof(float), static_cast<char const*>(0) + offset * sizeof(float)));
		GLcall(glVertexAttribDivisor(index, 1));

		m_addBuffer(vbo);

		vbo->unbind();
		unbind();
	}


	void VertexArray::bind() const
	{
		GLcall(glBindVertexArray(m_id));
	}

	void VertexArray::unbind()
	{
		GLcall(glBindVertexArray(0));
	}

	// Private Functions
	void VertexArray::m_addBuffer(VertexBuffer* vbo)
	{
		// Checking if Buffer is Already on Buffers List
		bool alreadyInVector = false;

		for (VertexBuffer* vboFromVector : m_buffers)
		{
			if (vboFromVector->getID() == vbo->getID())
			{
				alreadyInVector = true;

				break;
			}
		}

		// Adding Buffer to Buffers List
		if (!alreadyInVector)
			m_buffers.push_back(vbo);
		
	}

}