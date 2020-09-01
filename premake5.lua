

workspace "Xyla" -- ie. solution in vs
    architecture "x64"
    configurations { "Debug", "Release" }



    

project "Xyla"
    location "%{wks.name}"
    kind "ConsoleApp"
    language "C++"
    --staticruntime "on"

    targetdir "output/%{cfg.name}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
    objdir "intermidiaties/%{cfg.name}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

    pchheader "precompiled.h"
    pchsource "%{prj.name}/original/precompiled.cpp"

    files 
    {
        "%{prj.name}/original/**.h",
        "%{prj.name}/original/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/auxiliaries/SFML-2.5.1/include"

    }

    libdirs
    {
        "%{prj.name}/auxiliaries/SFML-2.5.1/lib"


    }


    links
    {
        

    }


    filter "system:Windows"
        cppdialect "C++17"
        systemversion "latest"

    filter "configurations:Debug"
        defines 
        { 
            "XYLA_DEBUG",
            "SFML_STATIC"
        }
        symbols "On"

        links
        {
            "winmm",
            "opengl32",
            "gdi32",
            "sfml-system-s-d",
            "sfml-window-s-d",
            "freetype",
            "sfml-graphics-s-d"

        }


       



    filter "configurations:Release"
        defines 
        { 
            "XYLA_RELEASE",
            "SFML_STATIC" 
    
        }
        optimize "On"

        links
        {
            "winmm",
            "opengl32",
            "gdi32",
            "sfml-system-s",
            "sfml-window-s",
            "freetype",
            "sfml-graphics-s"

        }