
/* INCLUDES */
// Self Include
#include "FrameBuffer.h"

// OpenGL Includes
#include <GL/glew.h>

// Header Includes
#include "../../Log.h"
#include "../ErrorHandling.h"



namespace gg
{

	/* Constructors */
	FrameBuffer::FrameBuffer()
	{
		// Creating FBO
		GLcall( glGenFramebuffers(1, &m_id) );

		// FBO Setup
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, m_id) );
		GLcall( glDrawBuffer(GL_COLOR_ATTACHMENT0) );

		// Finishing
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
	}

	/* Destructor */
	FrameBuffer::~FrameBuffer()
	{
		// Deleting Buffers and Textures
		GLcall( glDeleteFramebuffers(1, &m_id) );

		GLcall( glDeleteTextures(1, &m_colorTextureID) );
		GLcall( glDeleteTextures(1, &m_depthTextureID) );
		GLcall( glDeleteRenderbuffers(1, &m_depthBufferID) );
	}

	/* Functions */
	void FrameBuffer::attachTexture(const unsigned int width, const unsigned int height)
	{
		// Binding FBO
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, m_id) );

		// Creating Texture
		GLcall( glGenTextures(1, &m_colorTextureID) );

		// Depth Texture Setup
		GLcall( glBindTexture(GL_TEXTURE_2D, m_colorTextureID) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) );
		GLcall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr) );

		// Attaching Texture to FBO
		GLcall( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorTextureID, 0) );

		// Finishing
		GLcall( glBindTexture(GL_TEXTURE_2D, 0) );
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
	}

	void FrameBuffer::attachDepthTexture(const unsigned int width, const unsigned int height)
	{
		// Binding FBO
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, m_id) );

		// Creating Depth Texture
		GLcall( glGenTextures(1, &m_depthTextureID) );

		// Texture Setup
		GLcall( glBindTexture(GL_TEXTURE_2D, m_depthTextureID) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE) );
		GLcall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL) );
		GLcall( glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr) );

		// Attaching Depth Texture to FBO
		GLcall( glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTextureID, 0) );

		// Finishing
		GLcall( glBindTexture(GL_TEXTURE_2D, 0) );
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
	}

	void FrameBuffer::attachDepthBuffer(const unsigned int width, const unsigned int height)
	{
		// Binding FBO
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, m_id) );

		// Creating Depth Buffer
		GLcall( glGenRenderbuffers(1, &m_depthBufferID) );

		// Depth Buffer Setup
		GLcall( glBindRenderbuffer(GL_RENDERBUFFER, m_depthBufferID) );
		GLcall( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height) );
		GLcall( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferID) );

		// Finishing
		GLcall( glBindRenderbuffer(GL_RENDERBUFFER, 0) );
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
	}


	void FrameBuffer::bind(const unsigned int width, const unsigned int height) const
	{
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, m_id) );
		GLcall( glViewport(0, 0, width, height) );
	}

	void FrameBuffer::unbind(const unsigned int width, const unsigned int height)
	{
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
		GLcall( glViewport(0, 0, width, height) );
	}

	void FrameBuffer::unbind(const Window& window)
	{
		GLcall( glBindFramebuffer(GL_FRAMEBUFFER, 0) );
		GLcall( glViewport(0, 0, window.getWidth(), window.getHeight()) );
	}


	void FrameBuffer::bindColorTexture(const unsigned int slot) const
	{
		if (slot < 32)
		{
			GLcall( glActiveTexture(GL_TEXTURE0 + slot) );
			GLcall( glBindTexture(GL_TEXTURE_2D, m_colorTextureID) );
		}
		else
		{
			LOG("[Error] Color Texture Slot is out of range.");
		}
	}

	void FrameBuffer::bindDepthTexture(const unsigned int slot) const
	{
		if (slot < 32)
		{
			GLcall( glActiveTexture(GL_TEXTURE0 + slot) );
			GLcall( glBindTexture(GL_TEXTURE_2D, m_depthTextureID) );
		}
		else
		{
			LOG("[Error] Depth Texture Slot is out of range.");
		}
	}

}