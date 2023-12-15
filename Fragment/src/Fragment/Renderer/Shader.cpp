#include "frgpch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Fragment
{
	Shader::~Shader()
	{
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FRG_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		FRG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}

