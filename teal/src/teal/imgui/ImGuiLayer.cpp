#include "teal/imgui/ImGuiLayer.h"
#include <imgui.h>
#include "platform/opengl/imgui_impl_opengl3.h"
#ifdef TL_WIN32
#include "platform/win32/imgui_impl_win32.h"
#include "platform/win32/Win32Window.h"
#else
#error only windows is supported
#endif
#include "teal/core/KeyCode.h"
namespace Teal
{
	ImGuiLayer::ImGuiLayer(Application* app) : Layer("ImGui"), _App(app)
	{

	}
	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::onEvent(Event& event)
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		std::unique_ptr<Window>& window = _App->GetWindow();

#ifdef TL_WIN32
		ImGui_ImplWin32_Init(((Win32Window*)(window->GetWindowData()))->GetHwnd());
#else
#error only windows is supported
#endif
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::OnDetach()
{
#ifdef TL_WIN32
		ImGui_ImplWin32_Shutdown();
#else
#error only windows is supported
#endif
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
#ifdef TL_WIN32
		ImGui_ImplWin32_NewFrame();
#else
#error only windows is supported
#endif

		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		_App->GetWindow()->GetRenderingContext()->MakeCurrentContext();
	}

}