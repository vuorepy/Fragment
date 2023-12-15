#include "frgpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Fragment
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}