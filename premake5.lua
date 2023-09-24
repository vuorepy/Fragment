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
IncludeDirs["Glad"] = "Fragment/vendor/Glad/include"
IncludeDirs["ImGui"] = "Fragment/vendor/imgui"

include "Fragment/vendor/GLFW"
include "Fragment/vendor/Glad"
include "Fragment/vendor/imgui"

project "Fragment"
	location "Fragment"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.Glad}",
		"%{IncludeDirs.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "Default"
		staticruntime "On"
		systemversion "latest"

		defines {"FRG_PLATFORM_WINDOWS","FRG_BUILD_DLL", "GLFW_INCLUDE_NONE"}

		postbuildcommands
		{
			("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FRG_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Debug"
		defines "FRG_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Debug"
		defines "FRG_DIST"
		buildoptions "/MD"
		symbols "On"


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

	filter "configurations:Debug"
		defines "FRG_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Debug"
		defines "FRG_RELEASE"
		buildoptions "/MD"
		symbols "On"

	filter "configurations:Debug"
		defines "FRG_DIST"
		buildoptions "/MD"
		symbols "On"