#include "application.h"

#include <exception>
#include <iostream>

#include <WindowCreationFailException.h>
#include <GladInitializeFailException.h>

#include <math.h>

#include "../../Toolbox3D/Include/Matrix4.h"
#include <../Python/PythonUtility/PyUtility.h>
#include <../Python/PythonUtility/PyScripts.h>
#include <camera.h>
#include <buffer.h>

#include <glad.h>

Bwt::LowRenderer::Camera Bwt::Core::Application::camera = { {0.f, 0.f, 3.f},
Matrix4::GetPerspectiveMatrix(1980, 1080, 0.001f, 100.f, 90.f) };
bool UpdateCameraPython = false;

Bwt::Core::Application::Application(int width, int height, const char* title)
{
	if (!glfwInit())
		throw std::exception("Can't initialize glfw library !");

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw Bwt::Core::Debug::Exception::WindowCreationFailException("Creation of window failed");
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);

	try {
		InitializeGladLibrary();
	}
	catch (Bwt::Core::Debug::Exception::GladInitializeFailException e)
	{
		std::cerr << e.message << std::endl;
	}
}

Bwt::Core::Application::~Application()
{
	glfwTerminate();
}

void Bwt::Core::Application::SetBackGroundColor(Color color)
{
	bg = color;
}

void Bwt::Core::Application::SetBackGroundColor(float r, float g, float b, float a)
{
	bg = Color{ r, g, b, a };
}

void Bwt::Core::Application::AddShaderProgram(Bwt::Resources::Shader* shader)
{
	shaderProgram = shader;
}

void Bwt::Core::Application::RemoveShaderProgram(Bwt::Resources::Shader* shader)
{
	shaderProgram = nullptr;
}

void Bwt::Core::Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!UpdateCameraPython)
	{
		if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
			camera.Move(camera.transform.forward * camera.speed);
		if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
			camera.Move(camera.transform.forward.GetOpposed() * camera.speed);
		if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
			camera.Move(camera.transform.right * camera.speed);
		if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
			camera.Move(camera.transform.right.GetOpposed() * camera.speed);
		if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS))
			camera.Rotate({ 0.f, camera.speedRotation, 0.f });
		if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS))
			camera.Rotate({ 0.f, -camera.speedRotation, 0.f });
	}
	else
	{
		if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
			Bwt::PyUtility::GetModule("example_script")->Exec("update_camera", &camera, camera.transform.forward * camera.speed);
		if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
			Bwt::PyUtility::GetModule("example_script")->Exec("update_camera", &camera, camera.transform.forward.GetOpposed() * camera.speed);
		if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
			Bwt::PyUtility::GetModule("example_script")->Exec("update_camera", &camera, camera.transform.right * camera.speed);
		if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
			Bwt::PyUtility::GetModule("example_script")->Exec("update_camera", &camera, camera.transform.right.GetOpposed() * camera.speed);
		if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS))
			camera.Rotate({ 0.f, camera.speedRotation, 0.f });
		if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS))
			camera.Rotate({ 0.f, -camera.speedRotation, 0.f });
	}
	if (key == GLFW_KEY_F5 && action == GLFW_PRESS)
	{
		std::cout << "Hotreload : " << Bwt::PyUtility::HotReload() << " files updated" << std::endl;
	}
	if (key == GLFW_KEY_F6 && action == GLFW_PRESS)
	{
		if (UpdateCameraPython)
		{
			UpdateCameraPython = false;
			std::cout << "Camera update from python : OFF" << std::endl;
		}
		else
		{
			UpdateCameraPython = true;
			std::cout << "Camera update from python : ON" << std::endl;
		}
	}

}

void Bwt::Core::Application::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset != 0)
	{
		camera.Move(camera.transform.up * yoffset * camera.speed);
	}
}

void Bwt::Core::Application::Run(Scene* scene)
{
	float angle = 0.f;
	Bwt::PyUtility::Initialize();
	//Bwt::PyUtility::Print("example_script");
	Bwt::PyUtility::LoadModule("example_script");
	Bwt::PyUtility::GetModule("example_script")->Exec("greet");
	Bwt::PyUtility::GetModule("example_script")->Exec("add", 5, 5);

	Bwt::PyScripts* script = Bwt::PyUtility::GetModule("example_script");
	script->Start();

	using clock = std::chrono::steady_clock;

	auto now = clock::now();
	auto last = clock::now();
	float dt = 0.f;
	float accumulator = 0.f;
	const float fixedStep = 1.0f; // 1 second test for fixed update

	while (!glfwWindowShouldClose(window))
	{
		now = clock::now();
		std::chrono::duration<float> delta = now - last;
		last = now;
		dt = delta.count(); // second in float
		accumulator += dt;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 1.f, 1.f);

		script->Update(dt);

		while (accumulator >= fixedStep)
		{
			script->FixedUpdate(fixedStep);
			accumulator -= fixedStep;
		}

		script->LateUpdate();

		scene->renderScene(shaderProgram, &camera, angle);

		glfwSwapBuffers(window);
		glfwPollEvents();

		angle += 0.1f;
	}
}

void Bwt::Core::Application::InitializeGladLibrary()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw Bwt::Core::Debug::Exception::GladInitializeFailException("Fail when program try to load Gald library");
}

Bwt::Core::Color::Color(float r, float g, float b, float a) noexcept
	: r(r), g(g), b(b), a(a)
{
}