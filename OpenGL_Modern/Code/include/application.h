#pragma once



#include <shader.h>
#include <camera.h>
#include <buffer.h>

#include <scene.h>

namespace Bwt
{
	namespace Core
	{
		struct Color
		{
			float r;
			float g;
			float b;
			float a;

			Color(float r, float g, float b, float a = 1.f) noexcept;
		};

		class Application
		{
		private:

			GLFWwindow* window;
			Color bg = {0.2f, 0.3f, 0.3f, 1.f};
			Bwt::Resources::Shader* shaderProgram;

			void InitializeGladLibrary();

		public:

			static Camera camera;

			Application(int width, int height, const char* title);
			~Application();

			void SetBackGroundColor(Color color);
			void SetBackGroundColor(float r, float g, float b, float a = 1.f);

			void AddShaderProgram(Bwt::Resources::Shader* shader);
			void RemoveShaderProgram(Bwt::Resources::Shader* shader);

			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

			void Run(Scene* scene);

		};
	}
}