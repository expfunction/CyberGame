workspace "CyberGame"
    
    architecture "x86_64"
    
    language "C++"
	cppdialect "C++17"

    configurations { "Debug", "Release" }

project "Engine"
    kind "StaticLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "Engine/src/**.hpp", "Engine/src/**.cpp" }

    pchheader "CE_global.hpp"
	pchsource "CE_global.cpp"

    -- Add include directories 
    includedirs { "Libraries" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

-- Third party libraries linking
function linkGLFW()
	libdirs "Libraries/GLFW"

	filter "kind:not StaticLib"
		links "glfw3"
	filter {}
end

function linkGLEW()
	libdirs "Libraries/glew"

	filter "kind:not StaticLib"
		links "glew32"
	filter {}
end

function linkPNG()
	libdirs "Libraries/libpng"

	filter "kind:not StaticLib"
		links "libpng16"
	filter {}
end
-- End Third party

project "Game"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "Game/src/**.hpp", "Game/src/**.cpp" }
    
    includedirs { "Engine/src" }

    links { "Engine" }
    -- Users of Engine need to link GLFW
	linkGLFW()
	linkGLEW()
	linkPNG()

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

    filter { "system:windows" }
		links { "OpenGL32" }

	filter { "system:not windows" }
		links { "GL" }
