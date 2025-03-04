workspace "Veridox"
    configurations { "Debug", "Release" }
    platforms { "x86", "x64" }

    startproject "Veridox-Sample"
    defaultplatform "x64"

project "Veridox"
    location "Veridox"
    filename "Veridox"

    kind "StaticLib"
    staticruntime "On"

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

        links "libxl32.lib"

    filter "platforms:x64"
        architecture "x64"

        links "libxl64.lib"

    filter "configurations:Debug"
        defines "_DEBUG"
        runtime "Debug"
        
    filter "configurations:Release"
        runtime "Release"

project "Veridox-Sample"
    location "Veridox-Sample"
    filename "Veridox-Sample"

    kind "ConsoleApp"
    staticruntime "On"

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
        "%{wks.location}\\Dependencies\\include\\"
    }

    libdirs "%{wks.location}\\Dependencies\\lib"

    links "Veridox.lib"

    defines "_CONSOLE"
    debugdir "$(OutDir)"

    filter "platforms:x86"
        architecture "x32"
        defines "WIN32"

        links "libxl32.lib"
        postbuildcommands "copy /Y \"%{wks.location}Dependencies\\lib\\native\\libxl32.dll\" \"$(OutDir)libxl32.dll\""

    filter "platforms:x64"
        architecture "x64"

        links "libxl64.lib"
        postbuildcommands "copy /Y \"%{wks.location}Dependencies\\lib\\native\\libxl64.dll\" \"$(OutDir)libxl64.dll\""

    filter "configurations:Debug"
        defines "_DEBUG"
        runtime "Debug"
        
    filter "configurations:Release"
        runtime "Release"