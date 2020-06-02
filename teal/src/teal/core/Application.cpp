#include "teal/core/Application.h"
#include "teal/core/Window.h"
#include "teal/render/Shader.h"
#include "teal/render/Buffer.h"
#include <glad/glad.h>
#include <imgui.h>

namespace Teal 
{
	Application::Application() : p_Window(std::unique_ptr<Window>(new Window("Example"))), p_Running(false)
	{
		p_Window->SetEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
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

	void Application::PushLayer(LayerStack::StackObj layer)
	{
		p_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(LayerStack::StackObj layer)
	{
		p_LayerStack.PushOverlay(layer);
	}

	void Application::Run()
	{
		p_Running = true;

		GLfloat vertex_buffer_data[] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		unsigned int indices[] = { 0, 1, 2 };
		std::shared_ptr<Buffers::Vertex> vb = p_Window->GetRenderingContext()->NewVertexBuffer(vertex_buffer_data, sizeof(vertex_buffer_data));
		std::shared_ptr<Buffers::Index> ib = p_Window->GetRenderingContext()->NewIndexBuffer(indices, 3);

		GLuint vaId;
		glGenVertexArrays(1, &vaId);
		glBindVertexArray(vaId);

		vb->Bind();
		ib->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


		std::string vsrc;
		std::string fsrc;

		vsrc = R"(
			#version 410 core
			layout(location=0) in vec3 position;
			out vec3 v_pos;
			void main()
			{
				v_pos = position;
				gl_Position = vec4(position, 1.0);
			}
		)";
		fsrc = R"(
			#version 410 core
			in vec3 v_pos;
			out vec4 color;
			void main()
			{
				color = vec4(v_pos * 0.5 + 0.5, 1.0);
			}
		)";

		std::shared_ptr<Shader> shader = p_Window->GetRenderingContext()->NewShader(vsrc, fsrc);
		shader->Bind();

		while (p_Running)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(vaId);
			glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (auto layer : p_LayerStack)
				layer->OnUpdate();

			p_ImGuiLayer->Begin();
			ImGui::Text("Hello %s", "world");
			p_ImGuiLayer->End();

			p_Window->OnUpdate();
		}
	}
}
