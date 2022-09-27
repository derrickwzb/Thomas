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

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}

