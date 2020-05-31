#pragma once

#include "teal/core/Window.h"
#include "teal/core/Layer.h"
#include "teal/core/LayerStack.h"
#include "teal/Event.h"


namespace Teal 
{
	class TL_API Application : EventListener
	{
	public:
		Application();
		~Application();

		virtual void onEvent(Event& event);

		void PushLayer(LayerStack::StackObj layer);
		void PushOverlay(LayerStack::StackObj layer);

		void Run();
	protected:
		std::unique_ptr<Window> p_Window;
		bool p_Running;
		LayerStack p_LayerStack;
	};

	Application* CreateApplication();
}