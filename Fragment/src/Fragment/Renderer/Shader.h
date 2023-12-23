#pragma once

#include <string>

namespace Fragment
{
	class Shader
	{
	public:
		virtual ~Shader();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;
				
		static Ref<Shader> Create(const std::string& filePath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}