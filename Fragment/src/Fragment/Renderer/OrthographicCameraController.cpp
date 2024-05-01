#include "frgpch.h"
#include "OrthographicCameraController.h"

#include "Fragment/Core/Input.h"
#include "Fragment/Core/KeyCodes.h"


namespace Fragment
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		FRG_PROFILE_FUNCTION();

		m_CameraMoveSpeed = m_ZoomLevel;

		if (Input::IsKeyPressed(FRG_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(FRG_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (Input::IsKeyPressed(FRG_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(FRG_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& event)
	{
		FRG_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseScrolledEvent>(FRG_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FRG_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		FRG_PROFILE_FUNCTION();

		m_ZoomLevel -=  event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event)
	{
		FRG_PROFILE_FUNCTION();

		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}