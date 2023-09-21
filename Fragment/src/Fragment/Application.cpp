#include "frgpch.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Fragment/Log.h"

namespace Fragment {
	Fragment::Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Fragment::Application::~Application()
	{
	}

	void Application::Run() 
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}

