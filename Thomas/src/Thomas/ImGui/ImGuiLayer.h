/******************************************************************************/
/*!
\file		ImGuiLayer.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file represents the interface of the source file
			ImGuiLayer.cpp, it contains the function prototype declarations
			and class definition.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
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

