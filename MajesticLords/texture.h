#pragma once

#include <FreeImage/FreeImage.h>
#include <string>
#include <gl/glew.h>
#include "ImageLoad.h"

namespace MJ
{
	namespace graphics
	{
		class Texture
		{
		private:
			std::string m_FileName;
			GLuint m_TID;
			GLsizei m_Width, m_Height;
		public:
			Texture(std::string& path);
			~Texture();
			void bind() const;
			void unbind() const;

			inline unsigned int getWidth() { return m_Width; }
			inline unsigned int getHeight() { return m_Height; }
			inline unsigned int getID() { return m_TID; }
		private:
			GLuint load();

		};
	}
}