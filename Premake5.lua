workspace "kebsNet"
	configurations {"Debug", "Release"}
workspace "kebsNet"
	configurations {"Debug", "Release"}

project "kebsNet"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	includedirs{"$(SolutionDir)"}

	files {"**.h", "**.cpp",}
	files{
		"../asio1.28.0/include/*.cpp",
		"../asio1.28.0/include/*.hpp",
	}


	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "On"