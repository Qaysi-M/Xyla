

workspace "Xyla"
    architecture "x64"
    configurations { "Debug", "Release" }

project "Xyla"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"

    targetdir "output/%{cfg.name}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
    objdir "intermidiaties/%{cfg.name}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

    files 
    {
        "%{prj.name}/original/**.h",
        "%{prj.name}/original/**.cpp"
    }

    includedirs
    {


    }


    filter "system:Windows"
        cppdialect "C++17"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "XYLA_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "XYLA_RELEASE" }
        optimize "On"