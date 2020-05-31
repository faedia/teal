#include "teal/core/Application.h"
#include "teal/core/Window.h"
#include <glad/glad.h>

namespace Teal 
{
	Application::Application() : p_Window(std::unique_ptr<Window>(new Window("Example"))), p_Running(false)
	{
		p_Window->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::onEvent(Event& event)
	{
		TL_CORE_TRACE(event.ToString().c_str());

		for (auto it = p_LayerStack.end(); it != p_LayerStack.begin();)
		{
			(*--it)->onEvent(event);
			if (event.IsHandled())
				break;
		}
	}

	void Application::PushLayer(LayerStack::StackObj layer)
	{
		p_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(LayerStack::StackObj layer)
	{
		p_LayerStack.PushOverlay(layer);
	}

	void Application::Run()
	{
		p_Running = true;
		while (p_Running)
		{
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : p_LayerStack)
				layer->OnUpdate();
			p_Window->OnUpdate();
		}
	}
}
