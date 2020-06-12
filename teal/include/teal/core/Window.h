#pragma once

#include "teal/core/Common.h"
#include "teal/Event.h"
#include "teal/render/RenderingContext.h"
#include "teal/render/Renderer.h"
#include "Time.h"

namespace Teal
{
	class RenderingContext;
	class TL_API Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		Window(const std::string& name);
		~Window();
		
		unsigned int GetWidth() const { return 0; };
		unsigned int GetHeight() const { return 0; };

		void SetVSync(bool enabled);
		bool VsyncEnabled() const;

		inline std::unique_ptr<RenderingContext>& GetRenderingContext() { return _RenderingContext; }
		inline std::unique_ptr<Renderer>& GetRenderer() { return _Renderer; }
		inline std::shared_ptr<DeltaTime>& GetDeltaTime() { return _DeltaTime; }

		inline void* GetWindowData() const { return _WindowData; }

		void InitializeRenderingContext();

		void OnUpdate();

		virtual inline void SetEventCallback(const EventCallback& callback) { _EventCallback = callback; };

	private:
		EventCallback _EventCallback;
		void* _WindowData;
		std::shared_ptr<DeltaTime> _DeltaTime;
		std::unique_ptr<RenderingContext> _RenderingContext;
		std::unique_ptr<Renderer> _Renderer;
	};
}