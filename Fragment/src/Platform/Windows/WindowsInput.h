#pragma once

#include "Fragment/Core.h"
#include "Fragment/Input.h"

namespace Fragment
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImplementation(int keycode) override;

		virtual bool IsMouseButtonPressedImplementation(int button) override;
		virtual std::pair<float, float> GetMousePositionImplementation() override;
		virtual float GetMouseXImplementation() override;
		virtual float GetMouseYImplementation() override;

	};
}



