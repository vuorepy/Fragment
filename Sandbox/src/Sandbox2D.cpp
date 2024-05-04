#include "Sandbox2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	FRG_PROFILE_FUNCTION();

	m_CheckerboardTexture = Fragment::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	FRG_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Fragment::Timestep ts)
{
	FRG_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Fragment::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Fragment::RenderCommand::Clear();

	Fragment::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Fragment::Renderer2D::DrawQuad(m_SquarePosition, { 0.8f, 0.8f }, m_SquareColor);
	Fragment::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Fragment::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f}, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f, m_BackgroundColor);

	if (m_SquarePosition.y > 1.0f || m_SquarePosition.y < -1.0f)
	{
		m_MovementDirection *= -1.0f;
	}

	m_SquarePosition.y += m_MovementDirection * ts;


	Fragment::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	FRG_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::ColorEdit4("Background Color", glm::value_ptr(m_BackgroundColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Fragment::Event& event)
{
	m_CameraController.OnEvent(event);
}
