#pragma once
#include "layer.h"
#include "Font.h"
namespace MJ
{
	namespace graphics
	{
		class FontLayer : public Layer
		{
		private:
		public:
			FontLayer(Font* font,Shader* shader);
			~FontLayer();
		};
	}
}