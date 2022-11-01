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

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		glm::vec2 m_ViewportSize = {0.f,0.f};
		bool m_ViewportFocused = false;
	};
}

