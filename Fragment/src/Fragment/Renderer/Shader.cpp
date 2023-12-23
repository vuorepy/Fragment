#include "frgpch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Fragment
{
	Shader::~Shader()
	{
	}

	Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FRG_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGLShader>(filePath);
		}

		FRG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FRG_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		FRG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}

