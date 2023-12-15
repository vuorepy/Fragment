#pragma once

namespace Fragment
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case Fragment::ShaderDataType::Float:	return 4;
			case Fragment::ShaderDataType::Float2:	return 4 * 2;
			case Fragment::ShaderDataType::Float3:	return 4 * 3;
			case Fragment::ShaderDataType::Float4:	return 4 * 4;
			case Fragment::ShaderDataType::Mat3:	return 4 * 3 * 3;
			case Fragment::ShaderDataType::Mat4:	return 4 * 4 * 3;
			case Fragment::ShaderDataType::Int:		return 4;
			case Fragment::ShaderDataType::Int2:	return 4 * 2;
			case Fragment::ShaderDataType::Int3:	return 4 * 3;
			case Fragment::ShaderDataType::Int4:	return 4 * 4;
			case Fragment::ShaderDataType::Bool:	return 1;
		}

		FRG_CORE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case Fragment::ShaderDataType::Float:	return 1;
				case Fragment::ShaderDataType::Float2:	return 2;
				case Fragment::ShaderDataType::Float3:	return 3;
				case Fragment::ShaderDataType::Float4:	return 4;
				case Fragment::ShaderDataType::Mat3:	return 3 * 3;
				case Fragment::ShaderDataType::Mat4:	return 4 * 4;
				case Fragment::ShaderDataType::Int:		return 1;
				case Fragment::ShaderDataType::Int2:	return 2;
				case Fragment::ShaderDataType::Int3:	return 3;
				case Fragment::ShaderDataType::Int4:	return 4;
				case Fragment::ShaderDataType::Bool:	return 1;
			}

			FRG_CORE_ASSERT(false, "Unkown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& element)
			:m_Elements(element)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
 		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};
}
