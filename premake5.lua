workspace "Fragment"
	architecture "x64" 
	startproject "Sandbox"

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
IncludeDirs["glm"] = "Fragment/vendor/glm"
IncludeDirs["stb_image"] = "Fragment/vendor/stb_image"

include "Fragment/vendor/GLFW"
include "Fragment/vendor/Glad"
include "Fragment/vendor/imgui"

project "Fragment"
	location "Fragment"
	kind "StaticLib"
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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
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
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.Glad}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"FRG_PLATFORM_WINDOWS",
			"FRG_BUILD_DLL", 
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FRG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FRG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FRG_DIST"
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
		"Fragment/vendor/spdlog/include",
		"Fragment/src",
		"Fragment/vendor",
		"%{IncludeDirs.glm}"
	}

	links
	{
		"Fragment"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"FRG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FRG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FRG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FRG_DIST"
		runtime "Release"
		optimize "on"