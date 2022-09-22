#pragma once

#include "Thomas/Core/Layer.h"
#include "Thomas/Events/KeyEvent.h"
#include "Thomas/Events/ApplicationEvent.h"
#include "Thomas/Events/MouseEvent.h"


namespace Thomas {

	class THOMAS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnWindowResizedEvent(WindowResizeEvent& event);
	private:
		float m_Time = 0.0f;
	};

}

