#include "Font.h"

namespace MJ
{
	namespace graphics
	{

		Font::Font(std::string fontPath)
		{
			FT_Library ft;
			if (FT_Init_FreeType(&ft))
				std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

			FT_Face face;
			if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
				std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

			FT_Set_Pixel_Sizes(face, 0, 48);

			if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;


			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

			for (GLubyte c = 0; c < 128; c++)
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// Generate texture
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				
				// Now store character for later use
				Character character = {
					texture,
					maths::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					maths::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					face->glyph->advance.x
				};
				Characters.insert(std::pair<GLchar, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		//	FT_Done_Face(face);
			//FT_Done_FreeType(ft);

		}
	}
}