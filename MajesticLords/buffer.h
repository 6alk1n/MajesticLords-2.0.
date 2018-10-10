#pragma once

#include <gl/glew.h>

namespace MJ {
	namespace graphics
	{
		class Buffer
		{
		private:
			GLuint m_bufferID;
			GLuint m_ComponentCount;
		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~Buffer();
			inline GLuint getComponentCount() const { return m_ComponentCount; }

			void bind() const;
			void unbind() const;
		};
	}
}