#include <Thomas.h>

class Sandbox : public Thomas::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Thomas::Application* Thomas::CreateApplication()
{
	return new Sandbox();
}