#include "frgpch.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Fragment
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    FRG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGl:  return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		FRG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}