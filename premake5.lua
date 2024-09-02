workspace "test_vivid"
  location "build"
  cppdialect "C++latest"
  architecture "x86_64"

  configurations {
    "Debug",
    "Release"
  }

  project "test_vivid"
    kind "ConsoleApp"

    files {
      "sources/test.cpp",
      "sources/sndth/vivid.hpp"
    } includedirs {
      "sources"
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
