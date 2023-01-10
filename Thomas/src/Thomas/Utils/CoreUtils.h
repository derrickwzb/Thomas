/*!*************************************************************************
\file           CoreUtils.h
\author         Derrick Woo
\par DP email:  d.woo@digipen.edu
\par Programming CSD2400 Game project
\date           26/10/2022
\brief
This file contains declaration for functions used in FileDialogs class
****************************************************************************/
#pragma once

#include <string>

namespace Thomas
{
	class FileDialogs
	{
	public:
		static std::string OpenFile(const char* filter);

		static std::string SaveFile(const char* filter);
	private:

	};

}