#include "teal/core/Application.h"
#include "teal/core/Window.h"
#include <glad/glad.h>

namespace Teal 
{
	Application::Application() : _Window(std::unique_ptr<Window>(new Window("Example")))
	{
		_Window->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::onEvent(Event& event)
	{
		TL_CORE_TRACE(event.ToString().c_str());
	}

	void Application::Run()
	{
		while (true)
		{
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			_Window->OnUpdate();
		}
	}
}
