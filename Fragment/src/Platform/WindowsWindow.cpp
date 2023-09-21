#include "frgpch.h"
#include "WindowsWindow.h"

namespace Fragment
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	Fragment::WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	Fragment::WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void Fragment::WindowsWindow::Init(const WindowProperties& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		FRG_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWInitialized == false)
		{
			int success = glfwInit();

			if(success == false)
				FRG_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void Fragment::WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Fragment::WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool Fragment::WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void Fragment::WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}
