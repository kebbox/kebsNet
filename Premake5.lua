workspace "kebsNet"
	configurations {"Debug", "Release"}

project "kebsNet"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	includedirs{"$(SolutionDir)"}

	files {"**.h", "**.cpp",}


	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"
