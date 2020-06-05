#include "teal/core/Application.h"
#include "teal/core/Window.h"
#include "teal/render/Shader.h"
#include "teal/render/Buffer.h"
#include <imgui.h>

namespace Teal 
{
	Application::Application() : p_Window(std::unique_ptr<Window>(new Window("Example"))), p_Running(false)
	{
		p_Window->SetEventCallback([this](Event& event) {this->onEvent(event);});
		p_ImGuiLayer = std::shared_ptr<ImGuiLayer>(new ImGuiLayer(this));
		p_LayerStack.PushOverlay(p_ImGuiLayer, *p_Window->GetRenderer().get());
	}

	void Application::onEvent(Event& event)
	{
		for (auto it = p_LayerStack.end(); it != p_LayerStack.begin();)
		{
			if (event.IsHandled())
				break;
			(*--it)->onEvent(event);
		}
	}

	void Application::PushLayer(const LayerStack::StackObj& layer)
	{
		p_LayerStack.PushLayer(layer, *p_Window->GetRenderer().get());
	}

	void Application::PushOverlay(const LayerStack::StackObj& layer)
	{
		p_LayerStack.PushOverlay(layer, *p_Window->GetRenderer().get());
	}

	void Application::Run()
	{
		p_Running = true;

		while (p_Running)
		{
			p_Window->GetRenderer()->Begin();
			OnRender();
			p_Window->GetRenderer()->End();
			for (auto layer : p_LayerStack)
				layer->OnUpdate(*p_Window->GetRenderer().get());

			p_ImGuiLayer->Begin();
			ImGui::Text("Hello %s", "world");
			p_ImGuiLayer->End();

			p_Window->OnUpdate();
		}
	}
}
