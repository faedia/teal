#pragma once

#include "Common.h"
#include "teal/Event.h"

namespace Teal 
{
	class TL_API Application : EventListener
	{
	public:
		Application();
		~Application();

		virtual void onEvent(Event& event);

		void Run();
	};

	Application* CreateApplication();
}