#pragma once

#include "Thomas/Core/Layer.h"

namespace Thomas {

	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void OnAttach() {}
		void OnDetach() {}
		void OnEvent(Event& event);
		void OnUpdate();
	private:

	};

}

