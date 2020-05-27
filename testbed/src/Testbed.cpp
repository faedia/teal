#include <Teal.h>

class Testbed : public Teal::Application
{
public:
	Testbed()
	{
		_ClientLogger.Trace("The app has started!");
	}

	~Testbed()
	{

	}
private:
	Teal::Logger _ClientLogger = Teal::Logger("App");
};

Teal::Application* Teal::CreateApplication() 
{
	return new Testbed();
}
