#pragma once

#include "Fragment/Renderer/RendererAPI.h"

namespace Fragment
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}

