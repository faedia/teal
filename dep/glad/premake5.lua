project "glad"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")
    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        files
        {
            "include/glad/glad_wgl.h",
            "src/glad_wgl.c"
        }
        systemversion "latest"
        staticruntime "On"