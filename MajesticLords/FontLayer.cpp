#include "FontLayer.h"
#include "FontRenderer2D.h"
namespace MJ
{
	namespace graphics
	{
		FontLayer::FontLayer(Font* font, Shader* shader)
			: Layer(new FontRenderer2D(font,shader), shader, maths::mat4::orthographic(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f))
		{

		}

		FontLayer::~FontLayer()
		{

		}
	}
}