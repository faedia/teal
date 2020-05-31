#include <Teal.h>


Teal::Logger ClientLogger = Teal::Logger("App");

class ExampleLayer : public Teal::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override { ClientLogger.Info("Example::Update"); }
	void onEvent(Teal::Event& event) override { ClientLogger.Trace("{0}", event.ToString()); }
};

class Testbed : public Teal::Application
{
public:
	Testbed()
	{
		ClientLogger.Trace("The app has started!");
		PushLayer(Teal::LayerStack::StackObj(new ExampleLayer()));
	}

	~Testbed()
	{

	}
private:
};

Teal::Application* Teal::CreateApplication() 
{
	return new Testbed();
}
