#pragma once
#include <gl/glew.h>

namespace MJ {
	namespace graphics
	{
		class IndexBuffer
		{
		private:
			GLuint m_bufferID;
			GLuint m_Count;
		public:
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();

			inline GLuint getCount() const { return m_Count; }

			void bind() const;
			void unbind() const;
		};
	}
}