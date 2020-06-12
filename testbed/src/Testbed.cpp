#include <Teal.h>

Teal::Logger ClientLogger = Teal::Logger("App");
class Testbed;

class TestLayer : public Teal::Layer
{
	std::shared_ptr<Teal::VertexArray> va, sva;
	std::shared_ptr<Teal::Shader> shader, sshader;
	Teal::OrthographicCamera camera{ -1.6f, 1.6f, 0.9f, -0.9f, 1.0f, -1.0f };
	bool key[6] = { false, false, false, false, false, false };
public:
	TestLayer() : Layer("Test Layer")
	{
	}

	~TestLayer()
	{

	}

	void OnAttach(Teal::Renderer& renderer)
	{
		float vertex_buffer_data[] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
		};
		unsigned int indices[] = { 0, 1, 2 };

		va = renderer.NewVertexArray(
			{
				renderer.NewVertexBuffer(vertex_buffer_data, sizeof(vertex_buffer_data), {
					{Teal::Shader::Types::Float3, "position"},
					{Teal::Shader::Types::Float4, "color"}
				})
			},
			renderer.NewIndexBuffer(indices, 3)
		);


		float sdata[] =
		{
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f
		};
		unsigned int sidata[] = { 0, 1, 2, 2, 3, 0 };
		sva = renderer.NewVertexArray(
			{
				renderer.NewVertexBuffer(sdata, sizeof(sdata), {
					{Teal::Shader::Types::Float3, "position"}
				})
			},
			renderer.NewIndexBuffer(sidata, 6)
		);

		std::string svsrc;
		std::string sfsrc;

		svsrc = R"(
			#version 410 core
			layout(location=0) in vec3 position;
			uniform mat4 camera;
		
			out vec3 v_pos;

			void main()
			{
				v_pos = position;
				gl_Position = camera * vec4(position, 1.0);
			}
		)";
		sfsrc = R"(
			#version 410 core
			out vec4 color;
			in vec3 v_pos;
			void main()
			{
				float h = (v_pos.x * v_pos.x) + (v_pos.y * v_pos.y);
				if (h <= (0.75 * 0.75)) {
					color = vec4(0.4f, 0.1f, 0.9, 1.0);
				}
				else {color = vec4(0, 0, 0, 0);}
			}
		)";

		shader = renderer.NewShader("C:\\Users\\vaeco\\projects\\test.shader");
		sshader = renderer.NewShader(svsrc, sfsrc);

		//camera.Rotate(45.0f, { 0, 0, 1 });
	}

	void onEvent(Teal::Event& e)
	{
		if (e.GetEventType() == Teal::KeyPressedEvent::GetStaticType())
		{
			Teal::KeyPressedEvent* e1 = (Teal::KeyPressedEvent*)&e;
			if (e1->GetKeyCode() == TL_KB_D)
			{
				key[0] = true;
			}
			else if (e1->GetKeyCode() == TL_KB_A)
			{
				key[1] = true;
			}
			else if (e1->GetKeyCode() == TL_KB_W)
			{
				key[2] = true;
			}
			else if (e1->GetKeyCode() == TL_KB_S)
			{
				key[3] = true;
			}
			else if (e1->GetKeyCode() == TL_KB_Q)
			{
				key[4] = true;
			}
			else if (e1->GetKeyCode() == TL_KB_E)
			{
				key[5] = true;
			}
		}
		else if (e.GetEventType() == Teal::KeyReleasedEvent::GetStaticType())
		{
			Teal::KeyReleasedEvent* e1 = (Teal::KeyReleasedEvent*) & e;
			if (e1->GetKeyCode() == TL_KB_D)
			{
				key[0] = false;
			}
			else if (e1->GetKeyCode() == TL_KB_A)
			{
				key[1] = false;
			}
			else if (e1->GetKeyCode() == TL_KB_W)
			{
				key[2] = false;
			}
			else if (e1->GetKeyCode() == TL_KB_S)
			{
				key[3] = false;
			}
			else if (e1->GetKeyCode() == TL_KB_Q)
			{
				key[4] = false;
			}
			else if (e1->GetKeyCode() == TL_KB_E)
			{
				key[5] = false;
			}
		}
		else if (e.GetEventType() == Teal::MouseScrolledEvent::GetStaticType())
		{
			Teal::MouseScrolledEvent* e1 = (Teal::MouseScrolledEvent*) & e;
			float a = e1->GetY();
			if (a > 0)
			{
				camera.Scale({ 1.0f / 1.2f, 1.0f / 1.2f, 1.0f });
			}
			else
			{
				camera.Scale({ 1.2f, 1.2f, 1.0f });
			}
		}
	}

	void OnUpdate(const Teal::DeltaTime& dt, Teal::Renderer& renderer)
	{
		float tspeed = 1.0f * dt;
		float rspeed = 40.0f * dt;
		renderer.Clear({ 0.0f, 0.0f, 0.0f, 1.0f });
		renderer.Submit(sva, sshader, camera);
		renderer.Submit(va, shader, camera);
		camera.Translate({
			(key[0] ? tspeed : 0.0f) + (key[1] ? -tspeed : 0.0f),
			(key[2] ? tspeed : 0.0f) + (key[3] ? -tspeed : 0.0f),
			0.0f
		});

		camera.Rotate((key[4] ? rspeed : 0.0f) + (key[5] ? -rspeed : 0.0f), { 0, 0, 1 });
	}
};

class Testbed : public Teal::Application
{
public:
	Testbed()
	{
		ClientLogger.Trace("The app has started!");
		p_Window->SetVSync(false);
		PushLayer(std::shared_ptr<TestLayer>(new TestLayer()));
	}


	~Testbed()
	{

	}

	void OnRender()
	{
	}

private:
};

Teal::Application* Teal::CreateApplication() 
{
	return new Testbed();
}
