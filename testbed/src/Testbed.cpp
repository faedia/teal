#include <Teal.h>

class Testbed : public Teal::Application
{
public:
	Testbed()
	{

	}

	~Testbed()
	{

	}
};

Teal::Application* Teal::CreateApplication() 
{
	return new Testbed();
}
