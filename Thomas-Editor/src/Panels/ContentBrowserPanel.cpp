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
#include "Thomas/Renderer/Asset_Manager.h"

namespace Thomas
{

	//to change on projects
	extern const std::filesystem::path s_AssetsPath = "../Assets";


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

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;	

		ImGui::Columns(columnCount, 0, false);

		for (auto& dirEntry : std::filesystem::directory_iterator(m_CurrDirectory))
		{
			const auto& path = dirEntry.path();
			auto relPath = std::filesystem::relative(path, s_AssetsPath);
			std::string filenameString = relPath.filename().string();

			ImGui::PushID(filenameString.c_str());
			//Ref<Texture2D> icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)stash.Text_Storage["display"], {thumbnailSize, thumbnailSize}, {0, 1}, {1, 0});

			if (ImGui::BeginDragDropSource())
			{
				auto relativePath = std::filesystem::relative(path, s_AssetsPath);
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (dirEntry.is_directory())
					m_CurrDirectory /= path.filename();

			}
			ImGui::TextWrapped(filenameString.c_str());

			ImGui::NextColumn();

			ImGui::PopID();
		}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		ImGui::End();
	}
	
}