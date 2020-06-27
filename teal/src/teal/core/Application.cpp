#include "teal/core/Application.h"
#include "teal/core/Window.h"
#include "teal/render/Shader.h"
#include "teal/render/Buffer.h"
#include <imgui.h>
#include <deque>

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
		if (event.GetEventType() == EventType::WindowClose)
			p_Running = false;

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

		std::deque<double> times;

		while (p_Running)
		{
			p_Window->OnUpdate();
			p_Window->GetDeltaTime()->CalculateDelta();
			p_Window->GetRenderer()->Begin();
			OnRender();
			for (auto layer : p_LayerStack)
				layer->OnUpdate(*p_Window->GetDeltaTime(), *p_Window->GetRenderer().get());
			p_Window->GetRenderer()->End();

			if (times.size() == 50)
				times.pop_front();
			times.push_back(p_Window->GetDeltaTime()->GetSeconds());

			double avg = 0;
			for (auto t : times)
				avg += t;

			p_ImGuiLayer->Begin();
			ImGui::Text("Fps: %d", (int)round(1/(avg/times.size())));
			p_ImGuiLayer->End();

		}
	}
}
