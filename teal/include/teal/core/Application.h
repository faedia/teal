#pragma once

#include "Common.h"

namespace Teal 
{
	class TL_API 
	Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	TL_API Application* CreateApplication();
}