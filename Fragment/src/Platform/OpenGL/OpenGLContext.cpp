#include "frgpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>

namespace Fragment
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		FRG_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		FRG_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FRG_CORE_ASSERT(status, "Failed to initialize Glad!");

		FRG_CORE_INFO("OpenGL Info:");
		FRG_CORE_INFO("  Vendor:   {0}", (const char*) glGetString(GL_VENDOR));
		FRG_CORE_INFO("  Renderer: {0}", (const char*) glGetString(GL_RENDERER));
		FRG_CORE_INFO("  Version:  {0}", (const char*) glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		FRG_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}

