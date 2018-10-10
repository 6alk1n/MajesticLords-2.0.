#pragma once

#include "renderer2d.h"
#include "indexbuffer.h"
#include <cstddef>
#include "renderable2d.h"
#include "label.h"

namespace MJ {
	namespace graphics
	{

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3
		class FontRenderer2D : public Renderer2D
		{
		private:
			GLuint m_VAO;
			IndexBuffer* m_IBO;
			GLsizei m_IndexCount;
			GLuint m_VBO;
			VertexData* m_Buffer;
			std::vector<GLuint> m_TextureSlots;
			Font* m_Font;
			Shader* m_Shader;
		public:
			FontRenderer2D(Font* font,Shader* shader);
			~FontRenderer2D();
			void begin() override;
			void submit(const Renderable2D* renderable);
			void end() override;
			void flush();
		private:
			void init();
		};
	}
}