#pragma once
#include "Core.h"
#include "Timestep.h"
#include "Thomas/Events/Event.h"

namespace Thomas 
{

	class THOMAS_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event&) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected :
		std::string m_DebugName;
	};

}