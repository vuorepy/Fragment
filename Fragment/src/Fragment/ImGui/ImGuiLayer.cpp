#include "frgpch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Fragment/Application.h"
#include "Fragment/KeyCodes.h"

// TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Fragment
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = FRG_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = FRG_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = FRG_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = FRG_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = FRG_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = FRG_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = FRG_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = FRG_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = FRG_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = FRG_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = FRG_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = FRG_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = FRG_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = FRG_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = FRG_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = FRG_KEY_A;
		io.KeyMap[ImGuiKey_C] = FRG_KEY_C;
		io.KeyMap[ImGuiKey_V] = FRG_KEY_V;
		io.KeyMap[ImGuiKey_X] = FRG_KEY_X;
		io.KeyMap[ImGuiKey_Y] = FRG_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = FRG_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(FRG_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(FRG_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(FRG_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(FRG_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(FRG_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(FRG_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(FRG_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(FRG_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[FRG_KEY_LEFT_CONTROL] || io.KeysDown[FRG_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[FRG_KEY_LEFT_SHIFT] || io.KeysDown[FRG_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[FRG_KEY_LEFT_ALT] || io.KeysDown[FRG_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[FRG_KEY_LEFT_SUPER] || io.KeysDown[FRG_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int o = e.GetKeyCode();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}
}

