#include "thpch.h"
#include "ContentBrowserPanel.h"
#include "ImGui/imgui.h"



namespace Thomas
{

	//to change on projects
	static const std::filesystem::path s_AssetsPath = "assets";


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