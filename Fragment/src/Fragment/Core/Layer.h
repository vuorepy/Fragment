#pragma once

#include "Core.h"
#include "Timestep.h"

#include "Fragment/Events/Event.h"

namespace Fragment
{
	class FRAGMENT_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnUpdate(Timestep ts);
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event){}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}


