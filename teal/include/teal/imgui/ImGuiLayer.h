#pragma once

#include "teal/core/Layer.h"
#include "teal/Event.h"

namespace Teal {
	class TL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnAttach();
		void OnDetach();
		void OnUpdate() override;
		void onEvent(Event& event) override;

		bool onKeyTyped(KeyTypedEvent& event);
		bool onKeyPressed(KeyPressedEvent& event);
		bool onKeyReleased(KeyReleasedEvent& event);
		bool onMouseButtonPressed(MouseButtonPressedEvent& event);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& event);
		bool onMouseScrolled(MouseScrolledEvent& event);
		bool onMouseMoved(MouseMovedEvent& event);
		bool onWindowResize(WindowResizeEvent& event);
	private:

	};
}
