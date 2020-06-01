#include <Teal.h>

Teal::Logger ClientLogger = Teal::Logger("App");

class Testbed : public Teal::Application
{
public:
	Testbed()
	{
		ClientLogger.Trace("The app has started!");
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
