#pragma once

#include "Thomas.h"

namespace Thomas {
	class EditorLayer : public Thomas::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach()override;
		virtual void OnDetach()override;

		void OnUpdate(Timestep ts)override;
		virtual void OnImGuiRender()override;
		void OnEvent(Event& e)override;

	private:

		//camera controller
		std::shared_ptr <Framebuffer> m_Framebuffer;




	};
}

