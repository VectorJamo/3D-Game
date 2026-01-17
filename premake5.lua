workspace "3D-Game" --Solution name
	configurations { "Debug", "Release" }
	platforms { "x86", "x64" }

	filter "configurations:Debug"
		defines "DEBUG"
	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"
	filter "platforms:x86"
		system "Windows"
		architecture "x86"
	filter "platforms:x64"
		system "Windows"
		architecture "x86_64"
	
	project "3D-Game"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		
		location "3D-Game" 
		files { "3D-Game/src/**.h", "3D-Game/src/**.cpp", "3D-Game/src/**.c" } 
		includedirs { "Dependencies/GLFW/include", "Dependencies/GLAD/include", "Dependencies/glm" }
		libdirs { "Dependencies/GLFW/lib-vc2022" }
		links { "opengl32", "glfw3" }

		targetdir "bin/%{prj.name}/%{cfg.buildcfg}-%{cfg.platform}"
		objdir "bin-interm/%{prj.name}/%{cfg.buildcfg}-%{cfg.platform}"
