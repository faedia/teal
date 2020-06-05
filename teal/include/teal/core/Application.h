#pragma once

#include "teal/core/Window.h"
#include "teal/core/Layer.h"
#include "teal/core/LayerStack.h"
#include "teal/imgui/ImGuiLayer.h"
#include "teal/Event.h"

namespace Teal 
{
	class ImGuiLayer;
	class TL_API Application : EventListener
	{
	public:
		Application();
		virtual ~Application() = default;

		virtual void onEvent(Event& event);

		virtual void OnRender() = 0;

		void PushLayer(const LayerStack::StackObj& layer);
		void PushOverlay(const LayerStack::StackObj& layer);

		std::unique_ptr<Window>& GetWindow() { return p_Window; }

		void Run();
	protected:
		std::unique_ptr<Window> p_Window;
		bool p_Running;
		std::shared_ptr<ImGuiLayer> p_ImGuiLayer;
		LayerStack p_LayerStack;
	};

	Application* CreateApplication();
}