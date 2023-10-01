#pragma once

#include "Core.h"
#include "Window.h"
#include "Fragment/LayerStack.h"
#include "Fragment/Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Fragment/ImGui/ImGuiLayer.h"

namespace Fragment 
{
	class FRAGMENT_API Application
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
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};

	// To be defined in client
	Application* CreateApplication();
}


