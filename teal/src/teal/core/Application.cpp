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
		layer->OnAttach();
	}

	void Application::PushOverlay(LayerStack::StackObj layer)
	{
		p_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		p_Running = true;
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		while (p_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : p_LayerStack)
				layer->OnUpdate();
			p_Window->OnUpdate();
		}
	}
}
