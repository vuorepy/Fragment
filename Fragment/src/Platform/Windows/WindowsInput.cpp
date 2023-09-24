#include "frgpch.h"
#include "WindowsInput.h"

#include "Fragment/Application.h"
#include <GLFW/glfw3.h>

namespace Fragment
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImplementation(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImplementation(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImplementation()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float WindowsInput::GetMouseXImplementation()
	{
		auto [x, y] = GetMousePositionImplementation();

		return x;
	}

	float WindowsInput::GetMouseYImplementation()
	{
		auto[x, y] = GetMousePositionImplementation();

		return y;
	}
}