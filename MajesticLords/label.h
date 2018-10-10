#pragma once
#include "renderable2d.h"
#include "Font.h"
namespace MJ
{
	namespace graphics
	{
		class Label : public Renderable2D
		{
		private:
		public:
			std::string m_Text;
			Label(std::string text, float x, float y,maths::vec4 color);
			virtual void submit(Renderer2D* renderer) const override;
		};
	}
}