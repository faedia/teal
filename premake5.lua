workspace "teal"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "teal"
    location "teal"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "%{prj.location}/include/"
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

project "Testbed"
    location "Testbed"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs {
        "teal/include"
    }

    links {
        "teal"
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