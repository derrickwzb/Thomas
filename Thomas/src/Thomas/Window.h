#pragma once
#include "thpch.h"
#include "Thomas/Core.h"

namespace Thomas
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Thomas Engine",
			unsigned int width = 1920,
			unsigned int height = 1080)
			: Title(title), Width(width), Height(height)
		{
			//empty by design
		}

	};

	//interface for windows based desktop system
	class THOMAS_API Window
	{
	public:
		virtual ~Window() {};

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//window attributes



	};
}