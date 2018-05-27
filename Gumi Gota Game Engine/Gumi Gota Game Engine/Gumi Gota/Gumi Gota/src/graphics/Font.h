#ifndef GUMIGOTA_FONT_H
#define GUMIGOTA_FONT_H



/* INCLUDES */
// Normal Includes
#include <string>

// FreeType Includes
#include <ft2build.h>
#include FT_FREETYPE_H

// FreeType-GL Includes
#include "../../vendor/freetype-gl/freetype-gl-master/freetype-gl.h"



namespace gg
{

	class Font
	{
	private:
		/* Variables */
		ftgl::texture_atlas_t* m_atlas;
		ftgl::texture_font_t* m_font;

	public:
		/* Constructors */
		Font(const char* filename);
		
		/* Functions */
		void bindFontTexture() const;

		// Getters
		inline const unsigned int& getTextureID() const { return m_atlas->id; } /// consider removing l8r

	};

}



#endif