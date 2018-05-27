
/* INCLUDES */
// Self Include
#include "Font.h"

// OpenGL Includes
#include "GL/glew.h"

// Header Includes
#include "Error Handling.h"



namespace gg
{

	/* Constructors */
	Font::Font(const char* filename)
		: m_atlas(ftgl::texture_atlas_new(512, 512, 1)), m_font(ftgl::texture_font_new_from_file(m_atlas, 20, filename))
	{
		ftgl::texture_font_get_glyph(m_font, "Kappa");
	}

	/* Functions */
	void Font::bindFontTexture() const
	{
		GLcall(glBindTexture(GL_TEXTURE_2D, m_atlas->id));
	}

}