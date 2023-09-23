#include <Fragment.h>

class Sandbox : public Fragment::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Fragment::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Fragment::Application* Fragment::CreateApplication()
{
	return new Sandbox();
}
