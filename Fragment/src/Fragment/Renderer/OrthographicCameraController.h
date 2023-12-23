#pragma once

#include "Fragment/Renderer/OrthographicCamera.h"
#include "Fragment/Core/Timestep.h"

#include "Fragment/Events/ApplicationEvent.h"
#include "Fragment/Events/MouseEvent.h"

namespace Fragment
{
	class OrthographicCameraController
	{
	public: 
		OrthographicCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		float GetZoomLevel() const { return m_ZoomLevel; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraMoveSpeed = 1.0f;
	};
}