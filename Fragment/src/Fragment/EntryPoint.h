#pragma once

#ifdef FRG_PLATFORM_WINDOWS

extern Fragment::Application* Fragment::CreateApplication();

void main(int argc, char** argv)
{
	auto app = Fragment::CreateApplication();
	app->Run();
	delete app;
}

#endif