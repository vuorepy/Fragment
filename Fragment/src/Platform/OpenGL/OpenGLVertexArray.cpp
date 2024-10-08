#include "frgpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Fragment
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Fragment::ShaderDataType::Float:    return GL_FLOAT;
		case Fragment::ShaderDataType::Float2:   return GL_FLOAT;
		case Fragment::ShaderDataType::Float3:   return GL_FLOAT;
		case Fragment::ShaderDataType::Float4:   return GL_FLOAT;
		case Fragment::ShaderDataType::Mat3:     return GL_FLOAT;
		case Fragment::ShaderDataType::Mat4:     return GL_FLOAT;
		case Fragment::ShaderDataType::Int:      return GL_INT;
		case Fragment::ShaderDataType::Int2:     return GL_INT;
		case Fragment::ShaderDataType::Int3:     return GL_INT;
		case Fragment::ShaderDataType::Int4:     return GL_INT;
		case Fragment::ShaderDataType::Bool:     return GL_BOOL;
		}

		FRG_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		FRG_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		FRG_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		FRG_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		FRG_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer)
	{
		FRG_PROFILE_FUNCTION();

		FRG_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);

			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer>& indexBuffer)
	{
		FRG_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}

