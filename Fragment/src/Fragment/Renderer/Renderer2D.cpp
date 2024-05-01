#include "frgpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Fragment
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> Shader;
		Ref<Texture2D> BaseTexture;
	};

	static Renderer2DStorage* s_RendererStorage;

	void Renderer2D::Init()
	{
		FRG_PROFILE_FUNCTION();

		s_RendererStorage = new Renderer2DStorage();
		s_RendererStorage->VertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_RendererStorage->VertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_RendererStorage->VertexArray->SetIndexBuffer(squareIB);

		s_RendererStorage->BaseTexture = Texture2D::Create(1, 1);
		uint32_t baseTextureData = 0xffffffff;
		s_RendererStorage->BaseTexture->SetData(&baseTextureData, sizeof(baseTextureData));

		s_RendererStorage->Shader = Shader::Create("assets/shaders/Texture.glsl");
		s_RendererStorage->Shader->Bind();
		s_RendererStorage->Shader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		FRG_PROFILE_FUNCTION();

		delete s_RendererStorage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		FRG_PROFILE_FUNCTION();

		s_RendererStorage->Shader->Bind();
		s_RendererStorage->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		FRG_PROFILE_FUNCTION();

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		FRG_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_RendererStorage->Shader->SetMat4("u_Transform", transform);
		s_RendererStorage->Shader->SetFloat4("u_Color", color);

		s_RendererStorage->BaseTexture->Bind();
		s_RendererStorage->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererStorage->VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		FRG_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_RendererStorage->Shader->SetMat4("u_Transform", transform);
		s_RendererStorage->Shader->SetFloat4("u_Color", glm::vec4(1.0f));
		
		texture->Bind();
		s_RendererStorage->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_RendererStorage->VertexArray);
	}
}