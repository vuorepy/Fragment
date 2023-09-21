#pragma once

#ifdef FRG_PLATFORM_WINDOWS

extern Fragment::Application* Fragment::CreateApplication();

void main(int argc, char** argv)
{
	Fragment::Log::Init();
	FRG_CORE_INFO("Fragment Engine");

	auto app = Fragment::CreateApplication();
	app->Run();
	delete app;
}

#endif