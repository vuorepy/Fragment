#include <Fragment.h>

class Sandbox : public Fragment::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Fragment::Application* Fragment::CreateApplication()
{
	return new Sandbox();
}