project "Thomas-Script-CPP"
kind "StaticLib"
language "C++"
cppdialect "C++17"
staticruntime "on"
characterset ("MBCS") 
targetdir ("bin/" .. outputdir .. "/%{prj.name}")
objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


files
{
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"

}
includedirs
{
    "../Thomas/vendor/spdlog/include",
    "../Thomas/vendor/rapidjson/include",
    "../Thomas/src",
    "../Thomas/vendor",
    "../Thomas/vendor/glm",
    "../Thomas/vendor/freetype/include"
}
links
{
    "Thomas"
}

filter "system:linux"
    pic "On"

    systemversion "latest"
    staticruntime "On"


filter "system:windows"
    systemversion "latest"
    staticruntime "On"

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
    runtime "Debug"
    symbols "On"

filter "configurations:Release"
    runtime "Release"
    optimize "On"