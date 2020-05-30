#pragma once

#include "Common.h"
#include <string>
#include <memory>
#include <any>

#include "../render/RenderingContext.h"

namespace Teal
{
	class RenderingContext;
	class TL_API Window
	{
	public:
		Window(const std::string& name);
		~Window();
		
		unsigned int GetWidth() { return 0; };
		unsigned int GetHeight() { return 0; };

		void SetVSync(bool enabled) {};
		bool VsyncEnabled() { return 0; };

		void* GetWindowData() { return _WindowData; }

		void InitializeRenderingContext();

		void OnUpdate();

	private:
		void* _WindowData;
		RenderingContext* _RenderingContext = nullptr;
	};
}