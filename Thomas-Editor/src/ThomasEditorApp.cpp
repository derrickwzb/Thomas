/******************************************************************************/
/*!
\file		ThomasEditorApp.cpp
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	2/11/2022
\brief		This file is the main entry point for editor app

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include <Thomas.h>
#include "Thomas/Core/EntryPoint.h"

#include "EditorLayer.h"

#include "imgui/imgui.h"


namespace Thomas
{

	class HazelEditor : public Application
	{
	public:
		HazelEditor()
		{
			PushLayer(new EditorLayer());

		}
		~HazelEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new HazelEditor();
	}
}