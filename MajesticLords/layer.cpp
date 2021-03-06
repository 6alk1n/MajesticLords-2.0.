#include "layer.h"
namespace MJ
{
	namespace graphics
	{
		Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix)
			: m_Renderer(renderer),m_Shader(shader),m_ProjectionMatrix(projectionMatrix)
		{
			m_Shader->enable();
			m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
			m_Shader->disable();
		}
		Layer::~Layer()
		{
			delete m_Shader;
			delete m_Renderer;

			for (int i = 0; i < m_Renderables.size(); i++)
				delete m_Renderables[i];
		}
		void Layer::add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Layer::render()
		{
			m_Renderer->begin();

			int i = 0;
			for (const Renderable2D* renderable : m_Renderables)
			{
				renderable->submit(m_Renderer);
				
				//if (i++ % 2 == 0)
				//{
				//	m_Renderer->push(maths::mat4::translation(maths::vec3(5, 0, 0)));
				//	m_Renderer->submit(renderable);
				//	m_Renderer->pop();
				//} 
				//else
				//{
				//	m_Renderer->push(maths::mat4::translation(maths::vec3(0, 5, 0)));
				//	m_Renderer->submit(renderable);
				//	m_Renderer->pop();
				//}
			}
			m_Renderer->end();
			m_Renderer->flush();
		}
	}
}