workspace "Thomas"
	architecture "x64"
	startproject "Thomas-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
assetsdir = "../bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Thomas/vendor/glfw/include"
IncludeDir["GLEW"] = "Thomas/vendor/glew/include"
IncludeDir["ImGui"] = "Thomas/vendor/imgui"
IncludeDir["glm"] = "Thomas/vendor/glm"
IncludeDir["fmod"] = "Thomas/vendor/fmod/inc"
IncludeDir["freetype"] = "Thomas/vendor/freetype/include"
IncludeDir["mono"] = "Thomas/vendor/mono/include"
IncludeDir["ImGuizmo"] = "Thomas/vendor/ImGuizmo"
IncludeDir["CPPScripts"] = "Thomas-Script-CPP/src"
 
LibraryDir = {}
LibraryDir["fmod"] = "Thomas/vendor/fmod/lib"
LibraryDir["freetype"] = "Thomas/vendor/freetype/include"
LibraryDir["mono"] = "Thomas/vendor/mono/lib/%{cfg.buildcfg}"

PostDir = {}
PostDir["parentmono"] = "Canvas/mono"
PostDir["scriptresources"] = "Thomas/Resources"
PostDir["scriptvendor"] = "Thomas/vendor/mono"
PostDir["ImGuiConfig"] = "Thomas-Editor/imgui.ini"


group "Dependencies"
	include "Thomas/vendor/glfw"
	include "Thomas/vendor/glew"
	include "Thomas/vendor/imgui"
group ""

group "CSharp-Scripts"
     include "Thomas-ScriptCore"
group ""

group "CPP-Scripts"
     include "Thomas-Script-CPP"
group ""

project "Thomas"
	location "Thomas"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	characterset ("MBCS") 
	warnings "Extra"

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
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
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
		"%{IncludeDir.mono}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.CPPScripts}"


	}

	libdirs 
	{ 
		"%{LibraryDir.fmod}",
		"%{LibraryDir.mono}",
		"%{LibraryDir.freetype}"
	}

	links 
	{ 
		"glfw",
		"glew",
		"ImGui",
		"opengl32.lib",
		"mono-2.0-sgen",
		"freetype.lib"
	}
	disablewarnings {"4201","5205","4505","4189"}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLEW_STATIC",
			"TH_PLATFORM_WINDOWS",
			"TH_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"STB_IMAGE_IMPLEMENTATION"
		}
		linkoptions 
		{ 
			"-IGNORE:4099",
			"-IGNORE:4006" 
	 	}	

	filter "configurations:Debug"
		defines "TH_DEBUG"
		runtime "Debug"
		symbols "on"

		postbuildcommands 
    {
		-- inside Thomas
		"{MKDIR} %{cfg.targetdir}/Resources",
		"{COPY} ../%{PostDir.scriptresources} %{cfg.targetdir}/Resources",
		"{MKDIR} %{cfg.targetdir}/vendor/mono",
		"{COPY} ../%{PostDir.scriptvendor} %{cfg.targetdir}/vendor/mono",

		-- outside Thomas
		"{MKDIR} " .. assetsdir .. "/Assets",
		"{COPY} ../Assets " .. assetsdir .. "/Assets",
		"{COPY} ../%{PostDir.parentmono} " .. assetsdir .. "/"

    }
		
	filter "configurations:Release"
		defines "TH_RELEASE"
		runtime "Release"
		optimize "on"

		postbuildcommands 
    {
		-- inside Thomas
		"{MKDIR} %{cfg.targetdir}/Resources",
		"{COPY} ../%{PostDir.scriptresources} %{cfg.targetdir}/Resources",
		"{MKDIR} %{cfg.targetdir}/vendor/mono",
		"{COPY} ../%{PostDir.scriptvendor} %{cfg.targetdir}/vendor/mono",

		-- outside Thomas
		"{MKDIR} " .. assetsdir .. "/Assets",
		"{COPY} ../Assets " .. assetsdir .. "/Assets",
		"{COPY} ../%{PostDir.parentmono} " .. assetsdir .. "/"

    }

	filter "configurations:Dist"
		defines "TH_DIST"
		runtime "Release"
		optimize "on"

project "Canvas"
	location "Canvas"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	warnings "Extra"

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
		"Thomas/vendor/rapidjson/include",
		"Thomas/src",
		"Thomas/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.freetype}",
		"%{IncludeDir.mono}",
		"Thomas/src/Scene",
		"%{IncludeDir.CPPScripts}"
	}

	libdirs
    {
		"%{LibraryDir.mono}",
        "%{LibraryDir.fmod}"
    }

	links
	{
		"Thomas",
		"Thomas-Script-CPP"
	}

	

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TH_PLATFORM_WINDOWS"
		}
		linkoptions 
		{ 
			"-IGNORE:4099",
			"-IGNORE:4006" 
	 	}

	filter "configurations:Debug"
		defines "TH_DEBUG"
		runtime "Debug"
		symbols "on"
		kind "ConsoleApp"
		linkoptions {
			"/NODEFAULTLIB:libcmt.lib"
		}

		links
    {
		"mono-2.0-sgen",
        "fmodL_vc"
    }
    postbuildcommands 
    {
		"{COPY} ../%{LibraryDir.mono}/mono-2.0-sgen.dll %{cfg.targetdir}",
        "{COPY} ../%{LibraryDir.fmod}/fmodL.dll %{cfg.targetdir}",
		"{COPY}	../%{LibraryDir.freetype}/freetype.dll %{cfg.targetdir}"
		
    }

	filter "configurations:Release"
		defines "TH_RELEASE"
		runtime "Release"
		symbols "on"
		optimize "on"
		kind "WindowedApp"
		entrypoint "mainCRTStartup"
	
		links
    {
		"mono-2.0-sgen",
        "fmod_vc"
    }
    postbuildcommands 
    {
		"{COPY} ../%{LibraryDir.mono}/mono-2.0-sgen.dll %{cfg.targetdir}",
        "{COPY} ../%{LibraryDir.fmod}/fmod.dll %{cfg.targetdir}",
		"{COPY}	../%{LibraryDir.freetype}/freetype.dll %{cfg.targetdir}"
    }

	filter "configurations:Dist"
		defines "TH_DIST"
		runtime "Release"
		symbols "on"
		optimize "on"



project "Thomas-Editor"
	location "Thomas-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	warnings "Extra"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Thomas/vendor/spdlog/include",
		"Thomas/vendor/rapidjson/include",
		"Thomas/src",
		"Thomas/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.freetype}",
		"%{IncludeDir.mono}",
		"Thomas/src/Scene",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.CPPScripts}"
	}

	libdirs
    {
		"%{LibraryDir.mono}",
        "%{LibraryDir.fmod}"
    }


	links
	{
		"Thomas",
		"Thomas-Script-CPP"
	}

	-- filter "files:vendor/ImGuizmo/**.cpp"
	-- flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TH_PLATFORM_WINDOWS"
		}
		linkoptions 
		{ 
			"-IGNORE:4099",
			"-IGNORE:4006",
			"-IGNORE:4098"
	 	}

	filter "configurations:Debug"
		defines "TH_DEBUG"
		runtime "Debug"
		symbols "on"


		links
		{
			"mono-2.0-sgen",
			"fmod_vc"
		}
		postbuildcommands 
		{
			"{COPY} ../%{LibraryDir.mono}/mono-2.0-sgen.dll %{cfg.targetdir}",
			"{COPY} ../%{LibraryDir.fmod}/fmod.dll %{cfg.targetdir}",
			"{COPY}	../%{LibraryDir.freetype}/freetype.dll %{cfg.targetdir}",
			"{COPY}	../%{PostDir.ImGuiConfig} %{cfg.targetdir}"
		}
	

	filter "configurations:Release"
		defines "TH_RELEASE"
		runtime "Release"
		symbols "on"
		optimize "on"

		links
		{
			"mono-2.0-sgen",
			"fmod_vc"
		}
		postbuildcommands 
		{
			"{COPY} ../%{LibraryDir.mono}/mono-2.0-sgen.dll %{cfg.targetdir}",
			"{COPY} ../%{LibraryDir.fmod}/fmod.dll %{cfg.targetdir}",
			"{COPY}	../%{LibraryDir.freetype}/freetype.dll %{cfg.targetdir}",
			"{COPY}	../%{PostDir.ImGuiConfig} %{cfg.targetdir}"
		}
	

	filter "configurations:Dist"
		defines "TH_DIST"
		runtime "Release"
		symbols "on"
		optimize "on"



		
