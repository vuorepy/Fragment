#pragma once

#include "Core.h"
#include "Window.h"

#include "Fragment/Core/LayerStack.h"
#include "Fragment/Core/Timestep.h"

#include "Fragment/Events/Event.h"
#include "Fragment/Events/ApplicationEvent.h"

#include "Fragment/ImGui/ImGuiLayer.h"

namespace Fragment 
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}


