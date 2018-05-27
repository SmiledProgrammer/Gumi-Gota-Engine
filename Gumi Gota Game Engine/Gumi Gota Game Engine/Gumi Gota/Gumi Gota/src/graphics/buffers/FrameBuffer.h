#ifndef GUMIGOTA_FRAME_BUFFER_H
#define GUMIGOTA_FRAME_BUFFER_H



/* INCLUDES */
// Normal Incldues
#include <vector>

// Header Includes
#include "../Window.h"



namespace gg
{

	class FrameBuffer
	{
	private:
		/* Variables */
		unsigned int m_id;

		unsigned int m_colorTextureID;
		unsigned int m_depthTextureID;
		unsigned int m_depthBufferID;

	public:
		/* Constructors */
		FrameBuffer();

		/* Destructor */
		~FrameBuffer();

		/* Functions */
		void attachTexture(const unsigned int width, const unsigned int height);
		void attachDepthTexture(const unsigned int width, const unsigned int height);
		void attachDepthBuffer(const unsigned int width, const unsigned int height);

		void bind(const unsigned int width, const unsigned int height) const;
		static void unbind(const unsigned int width, const unsigned int height);
		static void unbind(const Window& window);

		void bindColorTexture(const unsigned int slot) const;
		void bindDepthTexture(const unsigned int slot) const;

	};

}



#endif