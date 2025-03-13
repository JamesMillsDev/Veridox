workspace "Veridox"
    configurations { "Debug", "Release" }
    platforms { "x86", "x64" }

    startproject "Veridox-Sample"
    defaultplatform "x64"

project "Veridox"
    location "Veridox"
    filename "Veridox"

    kind "StaticLib"
    staticruntime "Off"

    language "C++"
    cppdialect "C++20"

    targetdir "%{wks.location}\\Dependencies\\lib"
    objdir "Intermediate\\%{prj.name}"

    files
    {
        "%{prj.location}\\Public\\include\\**.h",
        "%{prj.location}\\Public\\source\\**.cpp",
        "%{prj.location}\\Private\\include\\**.h",
        "%{prj.location}\\Private\\source\\**.cpp"
    }

    includedirs
    {
        "%{prj.location}\\Public\\include\\",
        "%{prj.location}\\Private\\include\\",
        "%{wks.location}\\Dependencies\\include\\"
    }

    libdirs "%{wks.location}\\Dependencies\\lib"

    postbuildcommands
    {
        "xcopy /Y /q \"%{prj.location}Public\\include\\*.h\" \"$(SolutionDir)Dependencies\\include\\Veridox\\\""
    }

    filter "platforms:x86"
        architecture "x32"
        defines "WIN32"

    filter "platforms:x64"
        architecture "x64"

    filter "configurations:Debug"
        defines {"_DEBUG", "_ITERATOR_DEBUG_LEVEL=2" }
        runtime "Debug"
        links "xlntd.lib"
        
    filter "configurations:Release"
        runtime "Release"
        links "xlnt.lib"

project "Veridox-Sample"
    location "Veridox-Sample"
    filename "Veridox-Sample"

    kind "ConsoleApp"
    staticruntime "Off"

    language "C++"
    cppdialect "C++20"

    targetdir "Builds\\%{prj.name}"
    objdir "Intermediate\\%{prj.name}"

    dependson "Veridox"

    files
    {
        "%{prj.location}\\include\\**.h",
        "%{prj.location}\\source\\**.cpp"
    }

    includedirs
    {
        "%{prj.location}\\include\\",
        "Veridox\\Public\\include\\",
        "%{wks.location}\\Dependencies\\include\\"
    }

    libdirs "%{wks.location}\\Dependencies\\lib"

    links "Veridox.lib"

    defines "_CONSOLE"
    debugdir "$(OutDir)"

    filter "platforms:x86"
        architecture "x32"
        defines "WIN32"

    filter "platforms:x64"
        architecture "x64"

    filter "configurations:Debug"
        defines {"_DEBUG", "_ITERATOR_DEBUG_LEVEL=2" }
        runtime "Debug"
        
    filter "configurations:Release"
        runtime "Release"