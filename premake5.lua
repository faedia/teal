workspace "teal"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

startproject "testbed"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "teal"
    location "teal"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/include/**"
    }

    includedirs {
        "%{prj.location}/include/",
        "dep/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        defines {
            "TL_WINDOWS",
            "TL_DLL"
        }

    filter "configurations:Debug"
        defines "TL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TL_RELEASE"
        optimize "On"

project "testbed"
    location "testbed"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "teal/include",
        "dep/spdlog/include"
    }

    links {
        "teal"
    }

    postbuildcommands {
        ("{COPY} ../bin/" .. outputdir .. "/teal/ %{cfg.buildtarget.directory}")
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        defines {
            "TL_WINDOWS"
        }

    filter "configurations:Debug"
        defines "TL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "TL_RELEASE"
        optimize "On"