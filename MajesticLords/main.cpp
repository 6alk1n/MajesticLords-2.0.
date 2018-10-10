#include "window.h"
#include "maths.h"
#include "fileutils.h"
#include "shader.h"
#include "timer.h"

#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

#include "renderable2d.h"
#include "simple2drenderer.h"
#include "BatchRenderer2D.h"

#include "static_sprite.h"
#include "sprite.h"

#include <vector>
#include <time.h>

#include "tilelayer.h"
#include "group.h"
#include "texture.h"

#define BATCH_RENDERER 1
#include "Font.h"
#include "FontLayer.h"
#include "label.h"

#if 1

int main()
{
	using namespace MJ;
	using namespace graphics;
	using namespace maths;
	
	Window window("Majestic", 800, 600);
	
	Font* font = new Font("Data/fonts/Arial.ttf");

	//glViewport(0, 0, 400, 300); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnable(GL_CULL_FACE);

//	glClearColor(1.0f,1.0f,1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 800.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* fontShader = new Shader("font.vert", "font.frag");

	Shader* shader = new Shader("basic.vert","basic.frag");
	int a = 0;


	TileLayer layer(shader);
	FontLayer fontlayer(font, fontShader);

	fontlayer.add(new Label("Hello world!", 50.0f, 50.0f, maths::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

	std::string str("Data/c.png");
	std::string str3("Data/a.png");
	std::string str2("Data/d.png");
	Texture* ta = new Texture(str);
	Texture* tb = new Texture(str2);
	Texture* t = new Texture(str3);

	Texture* textures[] =
	{
		new Texture(str),
		new Texture(str2),
		new Texture(str3)
	};
	//glOrtho(0, 800, 0, 600, -1, 1);
	for (float y = 0.0f; y < 800; y+=32)
	{
		for (float x = 0.0f; x < 800; x+=32)
		{
			//layer.add(new Sprite(x,y,0.9f,0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0,1,1)));
			if (rand() % 4 == 0)
			  layer.add(new Sprite(x,y,32.0f,32.0f, maths::vec4(rand() % 1000 / 1000.0f, 0,1,1)));
			else
				layer.add(new Sprite(x, y, 32.0f, 32.0f, textures[rand() % 3]));
		}
	}
	//layer.add(new Sprite(5.0, 5.0, 10.0f, 10.0f, maths::vec4(1,1,1,1)));
	Timer time;
	float timer=0;



	//Simple2dRenderer simple;
	//Sprite* testTexture = new Sprite(0, 0, 4, 4, maths::vec4(1, 1, 1, 1));
	//	shader->setUniform1i("tex",0);

	GLint texIDs[] =
	{
		0,1,2,3,4,5,6,7,8,9
	};

	shader->enable();
	shader->setUniform1iv("textures", texIDs, 10);
	
	//shader->setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f,16.0f,-9.0f,9.0f,-1.0f,1.0f));
	shader->setUniformMat4("pr_matrix", maths::mat4::orthographic(0.0f,800.0f,0.0f,600.0f,-1.0f,1.0f));
	//shader->setUniformMat4("pr_matrix", ortho);
//shader->setUniform1i("tex", 0);

	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();		
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;
		double x, y;
		window.getMousePosition(x, y);
		double y2 = y - 300;

		//shader->setUniform2f("light_pos", vec2(-3,-3));	
		shader->enable();
		//shader->setUniform2f("light_pos", vec2((float)(x * 32 / 800.0f - 16.0f), (float)(9.0f - y * 18.0f / 600.0f)));
		shader->setUniform2f("light_pos", vec2(x,-y + 600));
		//layer.render();
		shader->disable();
		fontShader->enable();
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;


		fontShader->setUniformMat4("projection", maths::mat4::orthographic(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f));

		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;
		fontlayer.render();
	
		window.update(); 
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;
		fontShader->disable();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n",frames);
			frames = 0;
		}
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;
	}

	return 0;
}
#endif

