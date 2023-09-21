#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Fragment/Log.h"

namespace Fragment {
	Fragment::Application::Application()
	{
	}

	Fragment::Application::~Application()
	{
	}

	void Application::Run() {

		WindowResizeEvent e(1280, 720);
		FRG_TRACE(e);

		while (true)
		{

		}
	}
}

