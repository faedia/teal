#pragma once

#include "teal/core/Layer.h"
#include "teal/Event.h"
#include "teal/core/Application.h"

namespace Teal {
	class Application;
	class TL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(Application* app);
		~ImGuiLayer();

		virtual void onEvent(Event& event) override;

		void OnAttach(Renderer& renderer) override;
		void OnDetach() override;

		void Begin();
		void End();
	private:
		Application* _App;
	};
}
