#pragma once
#include "renderable2d.h"

#include <FreeType/ft2build.h>
#include FT_FREETYPE_H

#include <map>
namespace MJ
{
	namespace graphics
	{
		struct Character {
			GLuint     TextureID;  // ID handle of the glyph texture
			MJ::maths::vec2 Size;       // Size of glyph
			MJ::maths::vec2 Bearing;    // Offset from baseline to left/top of glyph
			GLuint     Advance;    // Offset to advance to next glyph
		};

		class Font
		{
		public:
			std::map<GLchar, Character> Characters;
		public:
			Font(std::string fontPath);
		};
	}
}