#include "teal/core/Application.h"
#include "teal/core/Window.h"
#include "teal/render/Shader.h"
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

		GLuint vaId;
		GLfloat vertex_buffer_data[] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		GLuint vbId;
		GLuint ibId;
		glGenVertexArrays(1, &vaId);
		glBindVertexArray(vaId);
		glGenBuffers(1, &vbId);
		glBindBuffer(GL_ARRAY_BUFFER, vbId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &ibId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibId);

		unsigned int indices[] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vsrc;
		std::string fsrc;

		vsrc = R"(
			#version 410 core
			layout(location=0) in vec3 position;
			void main()
			{
				gl_Position = vec4(position, 1.0);
			}
		)";
		fsrc = R"(
			#version 410 core
			out vec4 color;
			void main()
			{
				color = vec4(1.0, 0.0, 0.0, 1.0);
			}
		)";

		std::shared_ptr<Shader> shader = p_Window->GetRenderingContext()->NewShader(vsrc, fsrc);
		shader->Bind();

		while (p_Running)
		{
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(vaId);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (auto layer : p_LayerStack)
				layer->OnUpdate();

			p_ImGuiLayer->Begin();
			ImGui::Text("Hello %s", "world");
			p_ImGuiLayer->End();

			p_Window->OnUpdate();
		}
	}
}
