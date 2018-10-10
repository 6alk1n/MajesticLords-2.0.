#pragma once

#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
namespace MJ {
	namespace graphics {

 #define MAX_KEYS 1024
 #define MAX_BUTTONS 32

		
		class Window
		{
		private:
			const char* m_Title;
			int m_Width, m_Height;
			GLFWwindow* m_Window;
			bool m_Closed;

		    bool m_Keys[MAX_KEYS];
		    bool m_MouseButton[MAX_BUTTONS];
		    double mx, my;
		public:
			Window(const char* title, int width, int height);
			~Window();
			void update();
			bool closed() const;
			void clear() const;

			inline int getWidth() const { return m_Width; }
			inline int getHeight() const { return m_Height; }

			bool isKeyPressed(unsigned int keycode);
			bool isMouseButtonPressed(unsigned int button);
			void getMousePosition(double& x,double& y);
		private:
			bool init();
	
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			static void cursos_position_callback(GLFWwindow* window, double xpos,double ypos);
		};


} }