#include "frgpch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Fragment
{
	Ref<VertexArray> Fragment::VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FRG_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return std::make_shared<OpenGLVertexArray>();
		}

		FRG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}

