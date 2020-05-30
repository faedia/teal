#include "teal/core/Application.h"
#include "teal/core/Window.h"
#include <Windows.h>
#include <gl/GL.h>

namespace Teal 
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::onEvent(Event& event)
	{

	}

	void Application::Run()
	{
		Window window("Example");
		while (true)
		{
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			window.OnUpdate();
		}
	}
}
