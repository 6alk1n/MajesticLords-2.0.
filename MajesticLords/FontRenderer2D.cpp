#include "FontRenderer2D.h"


#include <iostream>

namespace MJ {
	namespace graphics
	{
		FontRenderer2D::FontRenderer2D(Font* font,Shader* shader)
		{
			m_Font = font;
			m_Shader = shader;
			init();
		}
		FontRenderer2D::~FontRenderer2D()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}
		void FontRenderer2D::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;

		}

		void FontRenderer2D::begin()
		{
			//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			//m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
		}
		void FontRenderer2D::submit(const Renderable2D* renderable)
		{

			glEnableClientState(GL_VERTEX_ARRAY);
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
			maths::vec4 col = renderable->getColor();
			maths::vec3 cols(col.x, col.y, col.z);
			 error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
			//glUniform3f(glGetUniformLocation(1, "textColor"), cols.x, cols.y, cols.z);
			m_Shader->setUniform3f("textColor",cols);
			 error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(m_VAO);
			Label* label = (Label*)renderable;
			// Iterate through all characters
			float scale = 5.0f;
			std::string::const_iterator c;
			GLfloat x = renderable->getPosition().x;
			GLfloat y = renderable->getPosition().y;
			 error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
			for (c = label->m_Text.begin(); c != label->m_Text.end(); c++)
			{
				Character ch = m_Font->Characters[*c];

				GLfloat xpos = x + ch.Bearing.x * scale;
				GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

				GLfloat w = ch.Size.x * scale;
				GLfloat h = ch.Size.y * scale;
				// Update VBO for each character
				GLfloat vertices[6][4] = {
					{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
				};

				//GLfloat vertices[4][4] = {
				//	{ xpos,     ypos    , 0, 0 },
				//{ xpos + w, ypos    , 1, 0 },
				//{ xpos,     ypos + h, 0, 1 },
				//{ xpos + w, ypos + h, 1, 1 },
				//};

				// Render glyph texture over quad

				error = glGetError();
				if (error != GL_NO_ERROR)
					std::cout << "OpenGL Error: " << error << std::endl;

				glBindTexture(GL_TEXTURE_2D, ch.TextureID);
				// Update content of VBO memory

				error = glGetError();
				if (error != GL_NO_ERROR)
					std::cout << "OpenGL Error: " << error << std::endl;

				glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

				error = glGetError();
				if (error != GL_NO_ERROR)
					std::cout << "OpenGL Error: " << error << std::endl;

				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

				error = glGetError();
				if (error != GL_NO_ERROR)
					std::cout << "OpenGL Error: " << error << std::endl;

				glBindBuffer(GL_ARRAY_BUFFER, 0);

				error = glGetError();
				if (error != GL_NO_ERROR)
					std::cout << "OpenGL Error: " << error << std::endl;

				// Render quad
				glDrawArrays(GL_TRIANGLES, 0, 6);

				error = glGetError();
				if (error != GL_NO_ERROR)
					std::cout << "OpenGL Error: " << error << std::endl;

				// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
				x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
			}
			 error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			/*
			float Triangle[] =
			{
				0.0, 20.0, 0.0,
				30.0, 0.0, 0.0,
				0.0, 15.5, 0.0
			};

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, Triangle);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			return;


			glBegin(GL_TRIANGLES);
			glVertex3fv(&Triangle[0]);
			glVertex3fv(&Triangle[3]);
			glVertex3fv(&Triangle[6]);
			glEnd();*/
		}
		void FontRenderer2D::end()
		{
		//	glUnmapBuffer(GL_ARRAY_BUFFER);
		//	glBindBuffer(GL_ARRAY_BUFFER, 0);
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
		}

		void FontRenderer2D::flush()
		{
	/*		for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);

			m_IBO->unbind();
			glBindVertexArray(0);
			m_IndexCount = 0;*/
		}
		
	}
}