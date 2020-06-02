#pragma once

#include "teal/core/Common.h"
#include "teal/Event.h"
#include "teal/render/RenderingContext.h"

namespace Teal
{
	class RenderingContext;
	class TL_API Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		Window(const std::string& name);
		~Window();
		
		unsigned int GetWidth() { return 0; };
		unsigned int GetHeight() { return 0; };

		void SetVSync(bool enabled);
		bool VsyncEnabled();

		std::unique_ptr<RenderingContext>& GetRenderingContext() { return _RenderingContext; }

		void* GetWindowData() { return _WindowData; }

		void InitializeRenderingContext();

		void OnUpdate();

		virtual inline void SetEventCallback(const EventCallback& callback) { _EventCallback = callback; };

	private:
		EventCallback _EventCallback;
		void* _WindowData;
		std::unique_ptr<RenderingContext> _RenderingContext;
	};
}