workspace "vivid"
  location "build"
  cppdialect "C++latest"
  architecture "x86_64"

  configurations {
    "Debug",
    "Release"
  }

  project "vivid"
    kind "ConsoleApp"

    files {
      "single_include/sndth/vivid.hpp",
      "main.cpp"
    } includedirs {
      "single_include"
    }

    filter "configurations:Debug"
      symbols "Full"

      flags {
        "MultiProcessorCompile"
      }

    filter "configurations:Release"
      optimize "Full"

      flags {
        "LinkTimeOptimization",
        "MultiProcessorCompile"
      }
