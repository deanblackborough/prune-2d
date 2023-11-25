project "Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++latest"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
       "Source",
       "../Vendor/glm",
       "../Vendor/imgui",
       "../Vendor/sol",
       "../Vendor/sdl/include",
       "../Vendor/lua",
       "../Vendor/spdlog/include",
       "../Vendor/entt/include"
   }

   libdirs
   {
       "../Vendor/sdl/lib/x64",
       "../Vendor/lua/lib"
   }
    
   links 
   {
       "SDL2.lib",
       "SDL2main.lib",
       "SDL2_image.lib",
       "SDL2_mixer.lib",
       "SDL2_ttf.lib"
   }
    
   linkoptions "liblua53.a"

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"