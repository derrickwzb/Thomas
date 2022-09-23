project "GLEW"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/GL/glew.h",
		"glew.cpp"
    }

	defines 
	{ 
		"GLEW_STATIC",
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
    {
        "include",
    }
	
	libdirs 
	{ "lib/Release/x64" }

	links
	{
		"opengl32.lib",
		"glew32s.lib"
	}
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"