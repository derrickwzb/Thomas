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


		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e)override;

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};

}

