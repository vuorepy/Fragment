#include "frgpch.h"
#include "IndexBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Fragment
{
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    FRG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGl:  return new OpenGLIndexBuffer(indices, size);
		}

		FRG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}