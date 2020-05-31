#include "teal/imgui/ImGuiLayer.h"
#include "../../platform/opengl/imgui_impl_opengl3.h"
#include "teal/core/KeyCode.h"
namespace Teal
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGui")
	{

	}
	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.DisplaySize = ImVec2(1264, 681);

		io.KeyMap[ImGuiKey_Tab] = TL_KB_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = TL_KB_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = TL_KB_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = TL_KB_UP;
		io.KeyMap[ImGuiKey_DownArrow] = TL_KB_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = TL_KB_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = TL_KB_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = TL_KB_HOME;
		io.KeyMap[ImGuiKey_End] = TL_KB_END;
		io.KeyMap[ImGuiKey_Insert] = TL_KB_INSERT;
		io.KeyMap[ImGuiKey_Delete] = TL_KB_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = TL_KB_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = TL_KB_SPACE;
		io.KeyMap[ImGuiKey_Enter] = TL_KB_ENTER;
		io.KeyMap[ImGuiKey_Escape] = TL_KB_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = TL_KB_ENTER;
		io.KeyMap[ImGuiKey_A] = 'A';
		io.KeyMap[ImGuiKey_C] = 'C';
		io.KeyMap[ImGuiKey_V] = 'V';
		io.KeyMap[ImGuiKey_X] = 'X';
		io.KeyMap[ImGuiKey_Y] = 'Y';
		io.KeyMap[ImGuiKey_Z] = 'Z';

		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void ImGuiLayer::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyTypedEvent>(std::bind(&ImGuiLayer::onKeyTyped, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::onKeyPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::onKeyReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::onMouseButtonPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::onMouseButtonReleased, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::onMouseScrolled, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::onMouseMoved, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&ImGuiLayer::onWindowResize, this, std::placeholders::_1));
	}

	bool ImGuiLayer::onKeyTyped(KeyTypedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		unsigned int kc = event.GetKeyCode();
		if (kc > 0 && kc < 0x10000)
			io.AddInputCharacter(kc);

		return false;
	}

	bool ImGuiLayer::onKeyPressed(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		int kc = event.GetKeyCode();
		io.KeysDown[kc] = true;
		
		io.KeyCtrl = io.KeysDown[TL_KB_LEFT_CONTROL] || io.KeysDown[TL_KB_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[TL_KB_LEFT_SHIFT] || io.KeysDown[TL_KB_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[TL_KB_LEFT_ALT] || io.KeysDown[TL_KB_RIGHT_ALT];
		io.KeySuper = io.KeysDown[TL_KB_LEFT_SUPER] || io.KeysDown[TL_KB_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::onKeyReleased(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		int kc = event.GetKeyCode();
		io.KeysDown[kc] = false;

		io.KeyCtrl = io.KeysDown[VK_CONTROL] || io.KeysDown[VK_LCONTROL] || io.KeysDown[VK_RCONTROL];
		io.KeyShift = io.KeysDown[VK_SHIFT] || io.KeysDown[VK_LSHIFT] || io.KeysDown[VK_RSHIFT];
		io.KeyAlt = io.KeysDown[VK_MENU] || io.KeysDown[VK_LMENU] || io.KeysDown[VK_RMENU];
		io.KeySuper = io.KeysDown[VK_LWIN] || io.KeysDown[VK_RWIN];

		return false;
	}

	bool ImGuiLayer::onMouseButtonPressed(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::onMouseButtonReleased(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::onMouseScrolled(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += event.GetX();
		io.MouseWheel += event.GetY();
		return false;
	}

	bool ImGuiLayer::onMouseMoved(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2((float)event.GetX(), (float)event.GetY());
		return false;
	}


	bool ImGuiLayer::onWindowResize(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		return false;
	}
}