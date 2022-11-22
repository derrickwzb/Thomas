/******************************************************************************/
/*!
\file		ContentBrowserPanel.cpp
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	2/11/2022
\brief		This file contains the definition of the object ContentBrowserPanel.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "thpch.h"
#include "ContentBrowserPanel.h"
#include "ImGui/imgui.h"

namespace Thomas
{
	static const std::filesystem::path s_AssetsPath = "../Assets";


	ContentBrowserPanel::ContentBrowserPanel()
		:m_CurrDirectory (s_AssetsPath)
	{
		
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");

		if (m_CurrDirectory != std::filesystem::path(s_AssetsPath))
		{
			if (ImGui::Button("<"))
			{
				m_CurrDirectory = m_CurrDirectory.parent_path();
			}
		}

		for (auto& dirEntry : std::filesystem::directory_iterator(m_CurrDirectory))
		{
			const auto& path = dirEntry.path();
			auto relPath = std::filesystem::relative(path, s_AssetsPath);
			std::string filenameString = relPath.filename().string();

			if (dirEntry.is_directory())
			{
				if (ImGui::Button(filenameString.c_str()))
				{
					m_CurrDirectory /= dirEntry.path().filename();
				}
			}
			else
			{
				if (ImGui::Button(filenameString.c_str()))
				{

				}
			}
		}

		ImGui::End();
	}
	
}