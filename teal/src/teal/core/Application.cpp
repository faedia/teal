#include "teal/core/Application.h"
#include "teal/core/Window.h"
#include "teal/render/Shader.h"
#include "teal/render/Buffer.h"
#include <glad/glad.h>
#include <imgui.h>
#include "teal/Math.h"

namespace Teal 
{
	Application::Application() : p_Window(std::unique_ptr<Window>(new Window("Example"))), p_Running(false)
	{
		p_Window->SetEventCallback([this](Event& event) {this->onEvent(event);});
		p_ImGuiLayer = std::shared_ptr<ImGuiLayer>(new ImGuiLayer(this));
		p_LayerStack.PushOverlay(p_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::onEvent(Event& event)
	{
		for (auto it = p_LayerStack.end(); it != p_LayerStack.begin();)
		{
			(*--it)->onEvent(event);
			if (event.IsHandled())
				break;
		}
	}

	void Application::PushLayer(const LayerStack::StackObj& layer)
	{
		p_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(const LayerStack::StackObj& layer)
	{
		p_LayerStack.PushOverlay(layer);
	}

	void Application::Run()
	{
		p_Running = true;

		GLfloat vertex_buffer_data[] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		};
		unsigned int indices[] = { 0, 1, 2 };
		
		std::shared_ptr<VertexArray> va = p_Window->GetRenderingContext()->NewVertexArray(
			{ 
				p_Window->GetRenderingContext()->NewVertexBuffer(vertex_buffer_data, sizeof(vertex_buffer_data), {
					{Shader::Types::Float3, "position"},
					{Shader::Types::Float4, "color"}
				})
			},
			p_Window->GetRenderingContext()->NewIndexBuffer(indices, 3)
		);


		GLfloat sdata[] =
		{
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};
		unsigned int sidata[] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<VertexArray> sva = p_Window->GetRenderingContext()->NewVertexArray(
			{
				p_Window->GetRenderingContext()->NewVertexBuffer(sdata, sizeof(sdata), {
					{Shader::Types::Float3, "position"}
				})
			},
			p_Window->GetRenderingContext()->NewIndexBuffer(sidata, 6)
		);

		std::string vsrc;
		std::string fsrc;

		vsrc = R"(
			#version 410 core
			layout(location=0) in vec3 position;
			layout(location=1) in vec4 color;			

			out vec3 v_pos;
			out vec4 v_color;
			void main()
			{
				v_pos = position;
				v_color = color;
				gl_Position = vec4(position, 1.0);
			}
		)";
		fsrc = R"(
			#version 410 core
			in vec3 v_pos;
			in vec4 v_color;
			out vec4 color;
			void main()
			{
				color = vec4(v_pos * 0.5 + 0.5, 1.0) * v_color;
			}
		)";

		std::shared_ptr<Shader> shader = p_Window->GetRenderingContext()->NewShader(vsrc, fsrc);

		std::string svsrc;
		std::string sfsrc;

		svsrc = R"(
			#version 410 core
			layout(location=0) in vec3 position;		
			void main()
			{
				gl_Position = vec4(position, 1.0);
			}
		)";
		sfsrc = R"(
			#version 410 core
			out vec4 color;
			void main()
			{
				color = vec4(0.4f, 0.1f, 0.9, 1.0);
			}
		)";

		std::shared_ptr<Shader>sshader = p_Window->GetRenderingContext()->NewShader(svsrc, sfsrc);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		while (p_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			Math::Vector<float, 4> vector({ 1.0f, 2.0f, 3.0f, 4.0f });

			//p_Window->GetRenderingContext()->BeginScene();
			//sshader->Bind();
			//p_Window->GetRenderingContext()->Submit(sva);
			//shader->Bind();
			//p_Window->GetRenderingContext()->Submit(va);
			//p_Window->GetRenderingContext()->EndScene();

			for (auto layer : p_LayerStack)
				layer->OnUpdate();

			p_ImGuiLayer->Begin();
			ImGui::Text("Hello %s", "world");
			p_ImGuiLayer->End();

			p_Window->OnUpdate();
		}
	}
}
