#include "frgpch.h"
#include "Texture.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Fragment
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FRG_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		FRG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}