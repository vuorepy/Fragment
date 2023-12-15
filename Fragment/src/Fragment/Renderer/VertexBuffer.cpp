#include "frgpch.h"
#include "VertexBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Fragment
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FRG_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		case RendererAPI::API::OpenGl:
			return new OpenGLVertexBuffer(vertices, size);
		}

		FRG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}