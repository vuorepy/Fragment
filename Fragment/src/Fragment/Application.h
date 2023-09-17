#pragma once

#include "Core.h"

namespace Fragment 
{
	class FRAGMENT_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}


