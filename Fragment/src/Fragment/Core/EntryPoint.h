#pragma once

#ifdef FRG_PLATFORM_WINDOWS

extern Fragment::Application* Fragment::CreateApplication();

void main(int argc, char** argv)
{
	Fragment::Log::Init();
	FRG_CORE_INFO("Fragment Engine");

	FRG_PROFILE_BEGIN_SESSION("Startup", "FragmentProfile-Startup.json");
	auto app = Fragment::CreateApplication();
	FRG_PROFILE_END_SESSION();

	FRG_PROFILE_BEGIN_SESSION("Runtime", "FragmentProfile-Runtime.json");
	app->Run();
	FRG_PROFILE_END_SESSION();

	FRG_PROFILE_BEGIN_SESSION("Shutdown", "FragmentProfile-Shutdown.json");
	delete app;
	FRG_PROFILE_END_SESSION();
}

#endif