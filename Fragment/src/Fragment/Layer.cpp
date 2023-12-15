#include "frgpch.h"
#include "Layer.h"

namespace Fragment
{
	Layer::Layer(const std::string& debugName)
		:m_DebugName(debugName)
	{
	}

	Layer::~Layer()
	{
	}
	void Layer::OnAttach()
	{
	}
	void Layer::OnDetach()
	{
	}
	void Layer::OnUpdate()
	{
	}
	void Layer::OnUpdate(Timestep ts)
	{
	}
}

