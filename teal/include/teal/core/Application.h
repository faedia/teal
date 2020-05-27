#pragma once

#include "Common.h"

namespace Teal 
{
	class TL_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	Application* CreateApplication();
}