#pragma once

#include "Fragment.h"

class Sandbox2D : public  Fragment::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Fragment::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Fragment::Event& event) override;

private:
	Fragment::OrthographicCameraController m_CameraController;

	Fragment::Ref<Fragment::VertexArray> m_SquareVA;
	Fragment::Ref<Fragment::Shader> m_FlatColorShader;

	Fragment::Ref<Fragment::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 m_BackgroundColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	glm::vec3 m_SquarePosition = { 0.0f, 0.0f, 0.0f };
	float m_MovementDirection = 1.0f;
};