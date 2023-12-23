#pragma once

#include "Fragment/Core/Layer.h"

#include "Fragment/Events/ApplicationEvent.h"
#include "Fragment/Events/MouseEvent.h"
#include "Fragment/Events/KeyEvent.h"

namespace Fragment
{
	class FRAGMENT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}


