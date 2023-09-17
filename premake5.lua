workspace "Fragment"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Fragment"
	location "Fragment"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "Default"
		staticruntime "On"
		systemversion "10.0.22621.0"

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
		systemversion "10.0.22621.0"

		defines 
		{
			"FRG_PLATFORM_WINDOWS"
		}
