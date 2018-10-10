#include "label.h"
namespace MJ
{
	namespace graphics
	{

		Label::Label(std::string text, float x, float y, maths::vec4 color)
			: Renderable2D(),m_Text(text)
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
		}
		void Label::submit(Renderer2D* renderer) const
		{

			renderer->submit(this);
		//	renderer->drawString(text, m_Position.x, m_Position.y, m_Color);
		}
	}
}