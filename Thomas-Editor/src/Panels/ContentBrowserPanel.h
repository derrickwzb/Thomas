#pragma once

#include "Thomas/Core/Core.h"

#include <filesystem>

namespace Thomas
{

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrDirectory;
	};
}