workspace "Thomas"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Thomas/vendor/glfw/include"
IncludeDir["GLEW"] = "Thomas/vendor/glew/include"
IncludeDir["ImGui"] = "Thomas/vendor/imgui"
IncludeDir["glm"] = "Thomas/vendor/glm"
IncludeDir["fmod"] = "Thomas/vendor/fmod/inc"
IncludeDir["freetype"] = "Thomas/vendor/freetype/include"

LibraryDir = {}
LibraryDir["fmod"] = "Thomas/vendor/fmod/lib"
LibraryDir["freetype"] = "Thomas/vendor/freetype/objs/x64/Debug"

include "Thomas/vendor/glfw"
include "Thomas/vendor/glew"
include "Thomas/vendor/imgui"

project "Thomas"
	location "Thomas"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "thpch.h"
	pchsource "Thomas/src/thpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb",
		"%{prj.name}/vendor/rapidjson/include",
		"%{prj.name}/vendor/freetype/include",
		"%{IncludeDir.fmod}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	libdirs 
	{ 
		"%{LibraryDir.fmod}",
		"%{LibraryDir.freetype}"
	}

	links 
	{ 
		"glfw",
		"glew",
		"ImGui",
		"opengl32.lib",
		"freetype.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLEW_STATIC",
			"TH_PLATFORM_WINDOWS",
			"TH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "TH_DEBUG"
		runtime "Debug"
		symbols "off"

	filter "configurations:Release"
		defines "TH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TH_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Thomas/vendor/spdlog/include",
		"Thomas/src",
		"Thomas/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.freetype}",
		"Thomas/src/Scene"
	}

	libdirs
    {
        "%{LibraryDir.fmod}"
    }

	links
	{
		"Thomas",
	}

	

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "TH_DEBUG"
		runtime "Debug"
		symbols "off"
		linkoptions {
			"/NODEFAULTLIB:libcmt.lib"
		}

		links
    {
        "fmodL_vc"
    }
    postbuildcommands 
    {
        "{COPY} ../%{LibraryDir.fmod}/fmodL.dll %{cfg.targetdir}",
		"{COPY}	../%{LibraryDir.freetype}/freetype.dll %{cfg.targetdir}"
    }

	filter "configurations:Release"
		defines "TH_RELEASE"
		runtime "Release"
		symbols "off"
		optimize "on"

		links
    {
        "fmod_vc"
    }
    postbuildcommands 
    {
        "{COPY} ../%{LibraryDir.fmod}/fmod.dll %{cfg.targetdir}",
		"{COPY}	../%{LibraryDir.freetype}/freetype.dll %{cfg.targetdir}"
    }

	filter "configurations:Dist"
		defines "TH_DIST"
		runtime "Release"
		symbols "off"
		optimize "on"