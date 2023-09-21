workspace "Fragment"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to the root folder
IncludeDirs = {}
IncludeDirs["GLFW"] = "Fragment/vendor/GLFW/include"

include "Fragment/vendor/GLFW"

project "Fragment"
	location "Fragment"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "frgpch.h"
	pchsource "Fragment/src/frgpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDirs.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "Default"
		staticruntime "On"
		systemversion "latest"

		defines {"FRG_PLATFORM_WINDOWS","FRG_BUILD_DLL"}

		postbuildcommands
		{
			("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Fragment/vendor/spdlog/include",
		"Fragment/src"
	}

	links
	{
		"Fragment"
	}

	filter "system:windows"
		cppdialect "Default"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"FRG_PLATFORM_WINDOWS"
		}
