#pragma once

#include <deque>
#include "static_sprite.h"
#include "renderer2D.h"

namespace MJ {
	namespace graphics
	{
		class Simple2dRenderer : public Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_RenderQueue;
		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};
	}
}
